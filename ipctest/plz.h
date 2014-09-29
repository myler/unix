#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

#define PLZ_STOP	0
#define PLZ_UP 		1
#define PLZ_DOWN	2
#define PLZ_LEFT	3
#define PLZ_RIGHT	4

//typedef unsigned char XML_Bool;

typedef unsigned char uchar;

uchar * plz_pelco_d_command_struct(uchar addr, int command_type);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
