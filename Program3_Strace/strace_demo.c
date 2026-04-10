/*
 * Program 3: strace Demo Program
 * Author: CHIRAG JINDANI
 * Date: 2025
 * Description: Demonstrates file I/O, console output, and process info
 *              so system calls can be clearly observed using strace.
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define FILENAME "strace_test.txt"
#define LINE     "======================================\n"

int main() {

    /* ── 1. Console Output (triggers write() syscall) ── */
    printf(LINE);
    printf("   STRACE DEMO PROGRAM\n");
    printf(LINE);
    printf("PID  : %d\n", getpid());
    printf("UID  : %d\n", getuid());

    /* ── 2. Write to File (triggers openat + write + close) ── */
    printf("\n[1] Writing to file: %s\n", FILENAME);
    FILE *fw = fopen(FILENAME, "w");
    if (!fw) { perror("fopen write"); return 1; }
    fprintf(fw, "Line 1: Hello from strace demo\n");
    fprintf(fw, "Line 2: File I/O triggers openat, write, close syscalls\n");
    fprintf(fw, "Line 3: PID = %d\n", getpid());
    fclose(fw);
    printf("    -> File written successfully.\n");

    /* ── 3. Read from File (triggers openat + read + close) ── */
    printf("\n[2] Reading back from file:\n");
    printf(LINE);
    char buf[256];
    FILE *fr = fopen(FILENAME, "r");
    if (!fr) { perror("fopen read"); return 1; }
    while (fgets(buf, sizeof(buf), fr)) {
        printf("    %s", buf);
    }
    fclose(fr);
    printf(LINE);

    /* ── 4. Done ── */
    printf("\n[3] Program complete. Observe syscalls with strace.\n");
    printf(LINE);

    return 0;
}