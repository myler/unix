#ifndef __CGI_UTILS_H__
#define __CGI_UTILS_H__

#include <sys/sem.h> 
#include <sys/ipc.h> 
#include "sem.h"
#include "logger.h"

//创建信号量 
int sem_creat(key_t key) 
{ 
    union semun sem; 
    int semid; 
    sem.val = 0; 
    semid = semget(key,1,IPC_CREAT |0777); 

    if (-1 == semid){ 
        printf("create semaphore error\n"); 
        return -1; 
    } 
    semctl(semid,0,SETVAL,sem); 
    return semid; 
} 

//删除信号量 
void del_sem(int semid) 
{ 
	union semun sem; 
	sem.val = 0; 
	semctl(semid,0,IPC_RMID,sem); 
} 

//创建信号量 
int new_sem(key_t key) 
{ 
	union semun sem; 
	int semid; 
	sem.val = 0; 
	semid = semget(key,0,0); 

	if (-1 == semid)
	{ 
		printf("create semaphore error\n"); 
		return-1; 
	} 

	return semid; 
} 


//p 操作
int p(int semid) 
{ 
    struct sembuf sops={0, -1,0}; 
    return (semop(semid,&sops,1)); 
} 

//v 操作
int v(int semid) 
{ 
    struct sembuf sops={0,1,0}; 
    return (semop(semid,&sops,1)); 
} 

//p 操作
void wait_v(int semid) 
{ 
    struct sembuf sops={0,-1,0}; 
    semop(semid,&sops,1); 
} 

//v 操作
void post_v(int semid) 
{ 
    struct sembuf sops={0,1,0}; 
    semop(semid,&sops,1); 
} 

#endif


