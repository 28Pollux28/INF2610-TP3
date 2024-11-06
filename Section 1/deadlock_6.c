#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#define N_THREADS 5

int flag = 0;

void* function_that_does_something(void* arg) {
    while (1) {
        if (flag)
            break;
    }
    pthread_exit(NULL);
}

void changeFlag(){
    if (rand() % 10 == 10)
        flag = 1;
    printf("Signal called\n");
}

int main() {
    pthread_t threads[N_THREADS];
 
    signal(SIGALRM, &changeFlag);      

    for(int i = 0; i < N_THREADS; i++){
        pthread_create(&threads[i], NULL, function_that_does_something, NULL);
    }

    alarm(1);

    for(int i = 0; i < N_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    return 0;
}

// Ici on a une situation d'interblocage car le thread principal attend la fin des threads fils qui attendent la mise à jour d'un flag de la part du thread principal qui ne peut arriver
// Exclusion mutuelle : Les threads fils et principal se partagent la ressource flag (lignes 14 et 22).
// Détention et attente : Les threads fils attendent la mise à jour du flag par le thread principal (ligne 13) et se détiennent eux-mêmes.
// Détenion et attente : Le thread principal attend la fin des threads fils (ligne 38) et détient le flag.
// Non-réquisition : Seul le thread principal peut mettre à jour le flag.
// Non-réquisition : Seuls les threads fils peuvent se terminer.
// Attente circulaire : Les threads fils attendent la mise à jour du flag par le thread principal qui attend la fin des threads fils (lignes 13 et 38).

// On a donc une situation d'interblocage.