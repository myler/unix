#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

void set_speed(int fd, int speed);
int set_Parity(int fd,int databits,int stopbits,int parity);
int OpenDev(char *Dev);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

