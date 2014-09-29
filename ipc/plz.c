#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */
#include "plz.h"
#include "serial_ctrl.h"
#include "config.h"
#include "logger.h"

#define STX 		0xFF
#define SPEED_H		0x00FF
#define SPEED_V		0xFF00

#define D_UP 		0x08
#define D_DOWN		0x10
#define D_LEFT		0x04
#define D_RIGHT		0x02

uchar command[6];

uchar checkSum()
{
    uchar sum;
    sum = (command[1]+command[2]+command[3]+command[4]+command[5]) % 0x100;
    return sum;
}

uchar * plz_pelco_d_command_struct(uchar addr, int command_type)
{
    memset(command, 7, 0);
    command[0] = STX;
    command[1] = addr;
    command[2] = 0;
    switch (command_type)
    {
    case PLZ_UP:
        command[3] = D_UP;
        memcpy(&command[4], SPEED_H, 2);
        command[6] = checkSum();
        break;
    case PLZ_DOWN:
        command[3] = D_DOWN;
        memcpy(&command[4], SPEED_H, 2);
        command[6] = checkSum();
        break;
    case PLZ_LEFT:
        command[3] = D_LEFT;
        memcpy(&command[4], SPEED_V, 2);
        command[6] = checkSum();
        break;
    case PLZ_RIGHT:
        command[3] = D_RIGHT;
        memcpy(&command[4], SPEED_V, 2);
        command[6] = checkSum();
        break;
    case PLZ_STOP:
        command[6] = checkSum();
        break;
    default:
        break;
    }
    return command;
}

int plz_start(s_var_ptz_control var_ptz_control)
{
    uchar * command;
    char dev[16];
    int fd;

    if (var_ptz_control.left == 1)
    {
        command = plz_pelco_d_command_struct(0x00, PLZ_LEFT);
    }
    else if (var_ptz_control.right == 1)
    {
        command = plz_pelco_d_command_struct(0x00, PLZ_RIGHT);
    }
    else if (var_ptz_control.up == 1)
    {
        command = plz_pelco_d_command_struct(0x00, PLZ_UP);
    }
    else if (var_ptz_control.down == 1)
    {
        command = plz_pelco_d_command_struct(0x00, PLZ_DOWN);
    }
    else
    {
        command = plz_pelco_d_command_struct(0x00, PLZ_STOP);
    }

    sprintf(dev, "/dev/tts/%d", var_ptz_control.channel+1);
    fd = OpenDev(dev);
	if(fd == -1){
		return -1;
	}
    set_speed(fd,19200);
    if (set_Parity(fd,8,1,'N') == 0)
    {
        logger(TLOG_ERROR, "Set Parity Error\n");
        close(fd);
        return -1;
    }
    if(write(fd, command, 7) != 7){
		logger(TLOG_ERROR, "serial send error\n");
		return -1;
    }
    close(fd);

    return 0;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

