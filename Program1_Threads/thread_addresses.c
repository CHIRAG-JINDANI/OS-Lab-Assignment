/*
 * program 1: observing variable addresses across multiple threads
 * author: chirag jindani
 * description: demonstrates how local and global variable addresses
 * differ across threads due to separate stack allocation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/* global variable - shared across all threads (lives in bss/data segment) */
int global_var = 100;

/* thread function */
void *thread_func(void *arg) {
    int thread_id = *((int *)arg);

    /* local variable - lives on this thread's stack */
    int local_var = thread_id * 10;

    printf("--------------------------------------------------\n");
    printf("thread id       : %d (pthread_t: %lu)\n", thread_id, pthread_self());
    printf("local  variable | value: %-5d | address: %p\n", local_var,  (void *)&local_var);
    printf("global variable | value: %-5d | address: %p\n", global_var, (void *)&global_var);
    printf("--------------------------------------------------\n");

    /* small sleep so output doesn't interleave */
    sleep(1);

    return NULL;
}

int main() {
    /* number of threads to create */
    #define NUM_THREADS 4

    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    printf("==================================================\n");
    printf("  program 1: thread variable address observation  \n");
    printf("==================================================\n");
    printf("main thread id  : %lu\n", pthread_self());
    printf("global variable | value: %-5d | address: %p\n", global_var, (void *)&global_var);
    printf("==================================================\n\n");

    /* create 4 threads */
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        if (pthread_create(&threads[i], NULL, thread_func, &thread_ids[i]) != 0) {
            perror("pthread_create failed");
            exit(EXIT_FAILURE);
        }
    }

    /* wait for all threads to finish */
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\n[main] all threads finished.\n");
    printf("[main] summary: local variables had different addresses per thread.\n");
    printf("[main] summary: global variable had the same address in all threads.\n");

    return 0;
}