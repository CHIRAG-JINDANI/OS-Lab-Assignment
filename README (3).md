# Operating Systems Lab — Assignment 3

**Name:** Chirag Jindani  
**Roll No:** 24AI020  
**Course:** Operating Systems Lab 3  
**Platform:** Ubuntu 22.04 (Docker Container)  
**Tools Used:** GCC, GDB, strace, top, pthread  

---

## Setup

- Windows with PowerShell and Git Bash
- Docker Desktop with Ubuntu 22.04 container
- Tools installed: `gcc`, `gdb`, `strace`, `top`, `pthread`

```bash
docker run -it --name os-lab \
  -v C:\Users\lenovo\OS-Lab-Assignment:/root/os-lab \
  --cap-add=SYS_PTRACE \
  ubuntu:22.04 bash

apt-get install -y gcc gdb strace procps file
```

---

## Program 1 — Thread Variable Addresses

**What it does:** Creates 4 threads using pthread and prints the memory address of a local and global variable from each thread.

**Run:**
```bash
gcc -o thread_addresses thread_addresses.c -lpthread
./thread_addresses
```

**Screenshots:**

![Thread Run 1](Program1_Threads/screenshots/threads_1.png)
![Thread Run 2](Program1_Threads/screenshots/threads2.png)
![Thread Run 3](Program1_Threads/screenshots/threads3.png)

**Observations:**
- Local variable addresses are different for every thread — each thread has its own stack
- Global variable address is the same across all threads — it lives in shared memory
- Addresses change between runs due to ASLR (Address Space Layout Randomization)
- Thread execution order changes every run — the OS scheduler decides it, not us

---

## Program 2 — Monitoring with top

**What it does:** Uses the `top` command to monitor CPU and memory usage before, during, and after compiling and running a CPU-intensive program.

**Run:**
```bash
gcc -O0 -o sample_program sample_program.c
./sample_program &
top
```

**Screenshots:**

![Before](Program2_Top/screenshots/top_before.png)
![During Compile](Program2_Top/screenshots/top_after.png)
![During Run](Program2_Top/screenshots/top_during_run.png)

**Observations:**
- Before anything: CPU was 98.1% idle, free memory was 2553.5 MiB
- During gcc compile: CPU usage went up, gcc + ld + collect2 appeared as processes
- During program run: `sample_program` used 100% CPU and ~101 MB of RAM
- Free memory dropped slightly during compilation (~3.8 MiB used)

---

## Program 3 — System Call Tracing with strace

**What it does:** Uses `strace` to trace all system calls made by a program and a shell command.

**Run:**
```bash
gcc -o strace_demo strace_demo.c
strace -e openat,read,write,close ./strace_demo 2>&1
strace -c ./strace_demo 2>&1
strace -e execve bash -c "cd /tmp" 2>&1
```

**Screenshots:**

![strace Output 1](Program3_Strace/screenshots/strace_ouput4%20(1).png)
![strace Output 2](Program3_Strace/screenshots/strace_ouput4%20(2).png)
![strace Output 3](Program3_Strace/screenshots/strace_ouput4%20(3).png)
![strace Output 4](Program3_Strace/screenshots/strace_ouput4%20(4).png)

**Observations:**
- `openat()` is called when we use `fopen()` to open a file
- `read()` and `write()` are called for file and console I/O
- `cd` is a shell built-in — it makes no `execve()` call at all
- Even a simple program makes 50+ system calls just during startup (loading libraries etc.)

---

## Program 4 — GDB Debugging

**What it does:** Writes a C program with loops, file I/O, pointers, and functions, then debugs it step by step using GDB.

**Run:**
```bash
gcc -g -Wall -o debug_program debug_program.c
./debug_program
gdb ./debug_program
```

**GDB commands used:**
```gdb
break main
run
print a
print b
print &a
next
continue
quit
```

**Screenshots:**

![Normal Run](Program4_GDB/screenshots/normal_run.png)
![Normal Run 2](Program4_GDB/screenshots/normal_run_2.png)
![Breakpoint and Variables](Program4_GDB/screenshots/breakpoint.png)
![Output File](Program4_GDB/screenshots/output_file.png)

**Observations:**
- `print &a` showed the exact memory address of variable `a` on the stack
- After `swap()`, values of a and b were correctly exchanged via pointers
- `backtrace` showed the full call chain from `main` to the current function
- `fflush()` forces buffered file output to be written to disk immediately

---

*Operating Systems Lab 3 — Chirag Jindani (24AI020)*
