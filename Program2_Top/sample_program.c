/*
 * program 2: system resource utilization monitor
 * author: chirag jindani
 * description: stresses cpu and memory to make them easily 
 * observable in the 'top' command for system analysis.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MEM_SIZE_MB 100  // adjust this to see a bigger jump in %mem

void stress_cpu() {
    // performing redundant math to keep the cpu busy
    double x = 1.5;
    for (int i = 0; i < 1000000; i++) {
        x *= 1.1;
        x /= 1.1;
    }
}

int main() {
    printf("==================================================\n");
    printf("  program 2: resource utilization observer        \n");
    printf("  process id (pid): %d                            \n", getpid());
    printf("==================================================\n");
    printf("1. check 'top' now to see baseline stats.\n");
    printf("2. this program will now stress cpu and memory...\n");
    printf("3. press ctrl+c to stop the program.\n");

    // memory stress: allocate and touch memory
    // simply allocating is not enough; we must write to it (memset)
    size_t bytes = (size_t)MEM_SIZE_MB * 1024 * 1024;
    char *buffer = malloc(bytes);

    if (buffer == NULL) {
        perror("failed to allocate memory");
        return 1;
    }

    printf("-> allocated %dmb. writing to memory...\n", MEM_SIZE_MB);
    memset(buffer, 'A', bytes); // force the os to map the pages

    // cpu stress: infinite loop to keep the process at the top of 'top'
    while (1) {
        stress_cpu();
    }

    // cleanup (never reached in this loop, but good practice)
    free(buffer);
    return 0;
}