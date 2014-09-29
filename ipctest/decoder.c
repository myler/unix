#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

#include "decoder.h"
#include <setjmp.h>

static const char * const cdjpeg_message_table[] = {
#include "cderror.h"
    NULL
};

typedef enum {
    FMT_BMP,		/* BMP format (Windows flavor) */
    FMT_GIF,		/* GIF format */
    FMT_OS2,		/* BMP format (OS/2 flavor) */
    FMT_PPM,		/* PPM/PGM (PBMPLUS formats) */
    FMT_RLE,		/* RLE format */
    FMT_TARGA,		/* Targa format */
    FMT_TIFF		/* TIFF format */
} IMAGE_FORMATS;

#ifndef DEFAULT_FMT		/* so can override from CFLAGS in Makefile */
#define DEFAULT_FMT	FMT_PPM
#endif

static IMAGE_FORMATS requested_fmt;

struct my_error_mgr {
  struct jpeg_error_mgr pub;	/* "public" fields */

  jmp_buf setjmp_buffer;	/* for return to caller */
};

typedef struct my_error_mgr * my_error_ptr;

static int error = 0;

int cinfo_setup (j_decompress_ptr cinfo)
{

    cinfo->err->trace_level = 0;

    //-bmp
    requested_fmt = FMT_BMP;

    //-color 256
//    cinfo->desired_number_of_colors = 256;
//    cinfo->quantize_colors = TRUE;

    //-scale 1/8
    cinfo->scale_num = 1;
    cinfo->scale_denom = 8;

    return 0;
}

METHODDEF(void)
my_output_message (j_common_ptr cinfo){
}

METHODDEF(void)
my_error_exit (j_common_ptr cinfo)
{
  /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
  my_error_ptr myerr = (my_error_ptr) cinfo->err;

  /* Always display the message. */
  /* We could postpone this until after returning, if we chose. */
  (*cinfo->err->output_message) (cinfo);

  /* Return control to the setjmp point */
  longjmp(myerr->setjmp_buffer, -1);
}

int jpeg_decoder(char *src, char *dst, int nSize)
{
//    fprintf(stderr, "djpeg enter\n");
	error = 0;
    double time_start = 0;//ms_time();
    double time_end = 0;
    struct jpeg_decompress_struct cinfo;
    struct my_error_mgr jerr;
//    int file_index;
    djpeg_dest_ptr dest_mgr = NULL;
//    FILE * input_file;
//    FILE * output_file;
    JDIMENSION num_scanlines;

    /* Initialize the JPEG decompression object with default error handling. */
    cinfo.err = jpeg_std_error(&(jerr.pub));
    jpeg_create_decompress(&cinfo);
    /* Add some application-specific error messages (from cderror.h) */
    jerr.pub.addon_message_table = cdjpeg_message_table;
    jerr.pub.first_addon_message = JMSG_FIRSTADDONCODE;
    jerr.pub.last_addon_message = JMSG_LASTADDONCODE;

	jerr.pub.error_exit = my_error_exit;
	jerr.pub.output_message = my_output_message;

	  if (setjmp(jerr.setjmp_buffer) == -1) {
	    /* If we get here, the JPEG code has signaled an error.
	     * We need to clean up the JPEG object, close the input file, and return.
	     */
//	    jpeg_destroy_decompress(&cinfo);
//		fprintf(stderr, "decoder corruptXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
	    return -1;
	  }

    /* Insert custom marker processor for COM and APP12.
     * APP12 is used by some digital camera makers for textual info,
     * so we provide the ability to display it as text.
     * If you like, additional APPn marker types can be selected for display,
     * but don't try to override APP0 or APP14 this way (see libjpeg.doc).
     */
//  jpeg_set_marker_processor(&cinfo, JPEG_COM, print_text_marker);
//  jpeg_set_marker_processor(&cinfo, JPEG_APP0+12, print_text_marker);


    time_start = ms_time();
    /* Specify data source for decompression */
    jpeg_stdio_src(&cinfo, src, nSize);

    /* Read file header, set default decompression parameters */
    (void) jpeg_read_header(&cinfo, TRUE);

    /* Adjust default decompression parameters by re-parsing the options */
//  file_index = parse_switches(&cinfo, argc, argv, 0, TRUE);
    cinfo_setup(&cinfo);

    /* Initialize the output module now to let it override any crucial
     * option settings (for instance, GIF wants to force color quantization).
     */
    switch (requested_fmt)
    {
#ifdef BMP_SUPPORTED
    case FMT_BMP:
        dest_mgr = jinit_write_bmp(&cinfo, FALSE);
        break;
//    case FMT_OS2:
//        dest_mgr = jinit_write_bmp(&cinfo, TRUE);
//        break;
#endif
#if 0
#ifdef GIF_SUPPORTED
    case FMT_GIF:
        dest_mgr = jinit_write_gif(&cinfo);
        break;
#endif
#ifdef PPM_SUPPORTED
    case FMT_PPM:
        dest_mgr = jinit_write_ppm(&cinfo);
        break;
#endif
#ifdef RLE_SUPPORTED
    case FMT_RLE:
        dest_mgr = jinit_write_rle(&cinfo);
        break;
#endif
#ifdef TARGA_SUPPORTED
    case FMT_TARGA:
        dest_mgr = jinit_write_targa(&cinfo);
        break;
#endif
#endif

    default:
        ERREXIT(&cinfo, JERR_UNSUPPORTED_FORMAT);
        break;
    }

    dest_mgr->output_file = dst;//output_file;

    /* Start decompressor */
    (void) jpeg_start_decompress(&cinfo);

    /* Write output file header */
//    (*dest_mgr->start_output) (&cinfo, dest_mgr);

    /* Process data */
    while (cinfo.output_scanline < cinfo.output_height)
    {
        num_scanlines = jpeg_read_scanlines(&cinfo, dest_mgr->buffer,
                                            dest_mgr->buffer_height);
//        (*dest_mgr->put_pixel_rows) (&cinfo, dest_mgr, num_scanlines);

        put_data(&cinfo, dest_mgr->buffer, &dst);
    }


    /* Finish decompression and release memory.
     * I must do it in this order because output module has allocated memory
     * of lifespan JPOOL_IMAGE; it needs to finish before releasing memory.
     */
//    (*dest_mgr->finish_output) (&cinfo, dest_mgr);
    (void) jpeg_finish_decompress(&cinfo);

    jpeg_destroy_decompress(&cinfo);

    time_end = ms_time();
//    fprintf(stderr, "time elapse:%f\n", time_end-time_start);

    /* All done. */
//	exit(jerr.num_warnings ? EXIT_WARNING : EXIT_SUCCESS);
	return(jerr.pub.num_warnings ? EXIT_WARNING : EXIT_SUCCESS);
//    return 0;			/* suppress no-return-value warnings */

}

int put_data(j_decompress_ptr cinfo, char ** src, char ** dst)
{
    char *inptr = src[0];
    char *outptr = *dst;
    int i;

    for (i = 0; i < cinfo->output_width; i++)
    {
        *outptr++ = *inptr++;	/* can omit GETJSAMPLE() safely */
    }

    /* Zero out the pad bytes. */
//  pad = dest->pad_bytes;
//  while (--pad >= 0)
//    *outptr++ = 0;

//	fprintf(stderr, "dst:%x-%x", *dst, outptr);
    *dst = outptr;

    return 0;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


