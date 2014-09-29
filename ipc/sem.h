
#ifndef __SEM_H__
#define __SEM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include <sys/sem.h>
#include <sys/ipc.h>

union semun { 
	int val; 
	struct semid_ds *buf; 
	unsigned short *array; 
} arg; 

typedef struct tag_syn_ctrl
{
    pthread_mutex_t     mutex_r, mutex_w; 
    pthread_cond_t      cond_r, cond_w;
    int                 flag_r, flag_w;
}s_syn_ctrl;

int thread_syn_init(pthread_mutex_t *mutex, pthread_cond_t *cond, int *flag);
int thread_syn_flag_set(pthread_mutex_t *mutex, pthread_cond_t *cond, int *flag);
int thread_syn_flag_clr(pthread_mutex_t *mutex, pthread_cond_t *cond, int *flag);
int thread_syn_wait(pthread_mutex_t *mutex, pthread_cond_t *cond, int *flag);
int sem_creat(key_t key);
void sem_del(int semid);
int p(int semid);
int v(int semid);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
