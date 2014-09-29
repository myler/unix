#ifndef __MD_H__
#define __MD_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

typedef struct tag_md_eara
{
    int x;
    int y;
    int w;
    int h;
} s_md_eara;

typedef struct tag_solution
{
    int x;          // ³¤
    int y;          // ¿í
} s_solution;


int md_check(char *buf_old, char *buf_new, int size, int sensitivity);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __VS_RECEIVER_H__ */
