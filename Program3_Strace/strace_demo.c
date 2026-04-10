#include <stdio.h>
#include <unistd.h> // Provides getpid and getuid

int main() {
    // 1. IDENTIFY 
    // These functions ask the OS for your "ID Card" info
    printf("I am Process ID: %d\n", getpid());
    printf("My User ID is: %d\n", getuid());

    // 2. WRITE
    // fopen "opens" a door to a file. 
    // "w" means we want to write.
    FILE *file = fopen("test.txt", "w");
    
    printf("Writing to file...\n");
    fprintf(file, "Hello! This is a test line.\n");
    
    fclose(file); // Close the door

    //  3. READ 
    // "r" means we want to read.
    file = fopen("test.txt", "r");
    char buffer[100];

    printf("Reading back from file:\n");
    // fgets grabs one line of text and puts it in 'buffer'
    while (fgets(buffer, 100, file)) {
        printf("File says: %s", buffer);
    }

    fclose(file);

    printf("Done! Now you can see these actions in strace.\n");
    return 0;
}
