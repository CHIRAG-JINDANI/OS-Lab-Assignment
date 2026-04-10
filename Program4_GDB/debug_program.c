#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int main() {
  int a = 25;
int b = 50;
int arr[] = {2, 4, 6};

printf("Before swap: a=%d, b=%d\n", a, b);

// 3. Pointers (GDB command: 'x/x' to examine memory)
swap(&a, &b);

printf("After swap: a=%d, b=%d\n", a, b);

// loop to track
for (int i = 0; i < 3; i++) {
    printf("Array index %d is %d\n", i, arr[i]);
}

// Dynamic memory (GDB command: 'print *ptr')
int *dyn = malloc(sizeof(int));
*dyn = 200;

printf("Dynamic value: %d\n", *dyn);

free(dyn);
return 0;
}
