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
        read(fd[0], string, 6); //Attente de la libération des ressources "Ecrivains du tube"
        exit(0);
    }

    if(!fork()){
        close(fd[1]);
        close(fd[0]);
        execlp("ls", "ls", "-l", NULL);
        exit(0);
    }

    char string[6] = "Salut!";
    write(fd[1], &string, strlen(string));
    printf("Process completed!\n");
    close(fd[0]);
    close(fd[1]);
    while(wait(NULL) > 0); //Attente de la libération des ressources "Processus Fils"
    return 0;
}



// Pour corriger le problème d'interblocage, la solution consiste à déplacer l'appel au wait après l'écriture dans le tube et la fermeture des descripteurs de fichiers du tube. (ligne 30)
// Cela permet au processus fils d'être libéré ce qui permet au processus parent de se terminer.