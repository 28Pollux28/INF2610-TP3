#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int fd[2];

    pipe(fd);

    if(!fork()){
        close(fd[1]);
        char* string[6];    
        read(fd[0], string, 6);
        exit(0);
    }

    if(!fork()){
        close(fd[1]);
        close(fd[0]);
        execlp("ls", "ls", "-l", NULL);
        exit(0);
    }

    while(wait(NULL) > 0);
    char string[6] = "Salut!";
    write(fd[1], &string, strlen(string));
    printf("Process completed!\n");
    close(fd[0]);
    close(fd[1]);
    return 0;
}