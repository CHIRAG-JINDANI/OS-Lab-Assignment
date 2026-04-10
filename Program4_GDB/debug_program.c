/*
 * Program 4: GDB Debugging Demo
 * Author: CHIRAG JINDANI
 * Date  : 2025
 * Description: Demonstrates loops, file I/O, functions, pointers,
 *              and memory referencing for GDB debugging session.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "debug_output.txt"
#define LINE "========================================\n"

/* ── Function 1: Find largest of two numbers ── */
int find_largest(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

/* ── Function 2: Swap two values using pointers ── */
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

/* ── Function 3: Sum array using a for loop ── */
int sum_array(int arr[], int size) {
    int total = 0;
    for (int i = 0; i < size; i++) {
        total += arr[i];
    }
    return total;
}

int main() {

    printf(LINE);
    printf("   PROGRAM 4: GDB DEBUGGING DEMO\n");
    printf(LINE);

    /* ── 1. Basic variables and pointer manipulation ── */
    int a = 10, b = 20;
    int *ptr_a = &a;
    int *ptr_b = &b;

    printf("\n[1] Pointer Manipulation:\n");
    printf("    a = %d  | address of a = %p\n", a, (void *)&a);
    printf("    b = %d  | address of b = %p\n", b, (void *)&b);
    printf("    *ptr_a  = %d\n", *ptr_a);
    printf("    *ptr_b  = %d\n", *ptr_b);

    /* ── 2. Find largest ── */
    int largest = find_largest(a, b);
    printf("\n[2] Largest of %d and %d = %d\n", a, b, largest);

    /* ── 3. Swap values ── */
    printf("\n[3] Before Swap: a = %d, b = %d\n", a, b);
    swap(&a, &b);
    printf("    After  Swap: a = %d, b = %d\n", a, b);

    /* ── 4. For loop with array ── */
    int arr[] = {5, 10, 15, 20, 25};
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("\n[4] Array elements:\n");
    for (int i = 0; i < size; i++) {
        printf("    arr[%d] = %d | address = %p\n",
               i, arr[i], (void *)&arr[i]);
    }
    printf("    Sum of array = %d\n", sum_array(arr, size));

    /* ── 5. While loop countdown ── */
    printf("\n[5] While loop countdown:\n");
    int count = 5;
    while (count > 0) {
        printf("    count = %d | address = %p\n", count, (void *)&count);
        count--;
    }

    /* ── 6. File I/O with output buffering ── */
    printf("\n[6] Writing results to file: %s\n", FILENAME);
    FILE *fp = fopen(FILENAME, "w");
    if (!fp) { perror("fopen"); return 1; }

    fprintf(fp, LINE);
    fprintf(fp, "   GDB DEBUG OUTPUT FILE\n");
    fprintf(fp, LINE);
    fprintf(fp, "a (after swap)     = %d\n", a);
    fprintf(fp, "b (after swap)     = %d\n", b);
    fprintf(fp, "largest(a,b)       = %d\n", largest);
    fprintf(fp, "sum of array       = %d\n", sum_array(arr, size));
    fprintf(fp, "address of a       = %p\n", (void *)&a);
    fprintf(fp, "address of arr[0]  = %p\n", (void *)&arr[0]);

    /* Explicit flush to show buffering concept */
    fflush(fp);
    fclose(fp);
    printf("    -> File written and flushed successfully.\n");

    /* ── 7. Dynamic memory allocation ── */
    printf("\n[7] Dynamic Memory:\n");
    int *dyn = (int *)malloc(3 * sizeof(int));
    if (!dyn) { perror("malloc"); return 1; }
    dyn[0] = 100; dyn[1] = 200; dyn[2] = 300;
    for (int i = 0; i < 3; i++) {
        printf("    dyn[%d] = %d | address = %p\n",
               i, dyn[i], (void *)&dyn[i]);
    }
    free(dyn);

    printf("\n" LINE);
    printf("   PROGRAM COMPLETE\n");
    printf(LINE);

    return 0;
}