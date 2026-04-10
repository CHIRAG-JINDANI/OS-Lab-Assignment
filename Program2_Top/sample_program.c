
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MEM_SIZE_MB 100  // adjust this to see a bigger jump in %mem

void stress_cpu() {
    double x = 1.7;
    for (int i = 0; i < 1200000; i++) {
        x *= 1.08;
        x /= 1.08;
    }
}

int main() {
    printf("  program 2: resource utilization observer        \n");
    printf("  process id (pid): %d                            \n", getpid());
    printf("1. check 'top' now to see baseline stats.\n");
    printf("2. this program will now stress cpu and memory...\n");
    printf("3. press ctrl+c to stop the program.\n");

    // simply allocating is not enough; we must write to it(memset)
    size_t bytes = (size_t)MEM_SIZE_MB * 1024 * 1024;
    char *buffer = malloc(bytes);

    if (buffer == NULL) {
        perror("failed to allocate memory");
        return 1;
    }

    printf("-> allocated %dmb. writing to memory...\n", MEM_SIZE_MB);
    memset(buffer, 'A', bytes); 
    while (1) {
        stress_cpu();
    }

    // cleanup (never reached in this loop, but good practice)
    free(buffer);
    return 0;
}
