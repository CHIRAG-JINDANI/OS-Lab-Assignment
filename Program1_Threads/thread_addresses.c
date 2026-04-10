#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// SHARED: Everyone sees the same global variable
int global_var = 100;

void* thread_work(void* arg) {
    int id = *(int*)arg;
    
    // PRIVATE: Each thread gets its own 'local_var' on its own stack
    int local_var = id * 10;

    printf("Thread %d: Global Addr: %p | Local Addr: %p\n", id, &global_var, &local_var);
    
    return NULL;
}

int main() {
    pthread_t threads[3];
    int ids[3] = {1, 2, 3};

    printf("Main:     Global Addr: %p\n\n", &global_var);

    // Create 3 threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, thread_work, &ids[i]);
    }

    // Wait for them to finish
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
