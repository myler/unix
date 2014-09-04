#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static int i = 1;

void* thread_1(void*);
void* thread_2(void*);

int main(void) {
    pthread_t tid_1;
    pthread_t tid_2;
    int err;

    if ((err = pthread_create(&tid_1, NULL, thread_1, (void*)NULL)) != 0)
        printf("can't create thread_1 errno = %d\n", err);
    if ((err = pthread_create(&tid_2, NULL, thread_2, (void*)NULL)) != 0)
        printf("can't create thread_2 errno = %d\n", err);

    pthread_join(tid_1, NULL);
    pthread_join(tid_2, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    exit(0);
}

void* thread_1(void* arg) {
    pthread_cleanup_push(pthread_mutex_unlock, &mutex);
    for (i = 1; i < 7; ++i) {
        pthread_mutex_lock(&mutex);
        printf("thread 1: lock %d\n", __LINE__);
        if (i % 3 == 0) {
            printf("thread 1: pre-signal %d\n", __LINE__);
            pthread_cond_signal(&cond);
            printf("thread 1: after-signal %d\n", __LINE__);
            sleep(1);
        }
        pthread_mutex_unlock(&mutex);
        printf("thread 1: unlock %d\n\n", __LINE__);
        sleep(1);
    }
    pthread_cleanup_pop(0);

    return (void*)0;
}

void* thread_2(void* arg) {
    pthread_cleanup_push(pthread_mutex_unlock, &mutex);
    while (i < 7) {
        pthread_mutex_lock(&mutex);
        printf("thread 2: lock %d\n", __LINE__);
        if (i % 3 != 0) {
            printf("thread 2: pre-wait %d\n", __LINE__);
            pthread_cond_wait(&cond, &mutex);
            printf("thread 2: after-wait %d\n", __LINE__);
        }
        pthread_mutex_unlock(&mutex);
        printf("thread 2: unlock %d\n\n", __LINE__);
        sleep(1);
    }
    pthread_cleanup_pop(0);

    return (void*)0;
}
