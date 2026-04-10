#include <stdio.h>
#include <stdlib.h>

// 1. A function to step into (GDB command: 'step')
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int main() {
    // 2. Variables to watch (GDB command: 'watch' or 'print')
    int a = 10;
    int b = 20;
    int arr[] = {5, 10, 15};

    printf("Before swap: a=%d, b=%d\n", a, b);

    // 3. Pointers (GDB command: 'x/x' to examine memory)
    swap(&a, &b);

    printf("After swap: a=%d, b=%d\n", a, b);

    // 4. A loop to track (GDB command: 'next' to go line by line)
    for (int i = 0; i < 3; i++) {
        printf("Array index %d is %d\n", i, arr[i]);
    }

    // 5. Dynamic memory (GDB command: 'print *ptr')
    int *dyn = malloc(sizeof(int));
    *dyn = 100;
    
    printf("Dynamic value: %d\n", *dyn);

    free(dyn);
    return 0;
}
