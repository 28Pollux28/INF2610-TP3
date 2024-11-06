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

    while(wait(NULL) > 0); //Attente de la libération des ressources "Processus Fils"
    char string[6] = "Salut!";
    write(fd[1], &string, strlen(string));
    printf("Process completed!\n");
    close(fd[0]);
    close(fd[1]);
    return 0;
}



// Le processus parent et le premier fils F1 sont dans une situation d'interbloquage.
// L'exclusion mutuelle est assurée par la séparation des deux processus (ligne 11 (premier fork))
// Ici nous avons deux ressources à considérer : les écrivains du tube et les processus fils.
// Pour la détention et attente, le processus fils F1 se détient lui-même et demande la ressource "libération des ecrivains du tube" (ligne 14).
// Pour la détention et attente, le processus parent détient un écrivain du tube et demande la ressource "libération des processus Fils" (ligne 25).
// Pour la non-réquisition, seul le processus Fils F1 peut libérer la ressource associée à lui-même vis-à-vis de son parent
// Pour la non-réquisition, seul le processus parent peut libérer son écrivain du tube.
// Attente circulaire : Le processus fils attend la libération de l'écrivain du processus parent qui attend la libération du processus fils. (ligne 14 et 25)