#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#define BUFFER_SIZE 5
#define N_THREADS 1
#define N_THREADS_2 10

int buffer[BUFFER_SIZE];
int ip;
int ic;

sem_t sem_initial;
sem_t sem_busy;
sem_t sem_critical;

int flag = 0;

void* producer(void* arg) {
    while (1) {
        sem_wait(&sem_initial);
        sem_wait(&sem_critical); //Exclusion mutuelle
        buffer[ip] = rand() % 9 + 1;
        ip = (ip + 1) % BUFFER_SIZE;
        sem_post(&sem_critical);//Fin Exclusion mutuelle
        sem_post(&sem_busy);
        if (flag)
            break;
    }
    pthread_exit(NULL);
}

void* consumer(void* arg) {
    while (1) {
        sem_wait(&sem_busy);
        sem_wait(&sem_critical);//Exclusion mutuelle
        int x = buffer[ic];
        ic = (ic + 1) % BUFFER_SIZE;
        sem_post(&sem_critical);//Fin Exclusion mutuelle
        sem_post(&sem_initial);
        if(x == 0){
            break;
        }
    }
    pthread_exit(NULL);
}

void changeFlag(){
    flag = 1;
    printf("Flag changed\n");
}

int main() {
    pthread_t prod_thread[N_THREADS], cons_thread[N_THREADS_2];

    sem_init(&sem_initial, 0, BUFFER_SIZE);
    sem_init(&sem_busy, 0, 0);           
    sem_init(&sem_critical, 0, 1); 
    signal(SIGALRM, &changeFlag);      

    for(int i = 0; i < N_THREADS; i++){
        pthread_create(&prod_thread[i], NULL, producer, NULL);
    }

    for(int i = 0; i < N_THREADS_2; i++){
        pthread_create(&cons_thread[i], NULL, consumer, NULL);
    }

    alarm(1);

    for(int i = 0; i < N_THREADS; i++){
        pthread_join(prod_thread[i], NULL);
    }

    for(int i = 0; i < N_THREADS_2; i++){
        buffer[ip] = 0;
        ip = (ip + 1) % BUFFER_SIZE;
    }

    for(int i = 0; i < N_THREADS_2; i++){
        pthread_join(cons_thread[i], NULL);
    }

    sem_destroy(&sem_initial);
    sem_destroy(&sem_busy);
    sem_destroy(&sem_critical);

    return 0;
}


// La situation d'interbloquage est ici crée par l'attente par le thread principale de la fin des threads consommateurs, qui sont eux-mêmes en attente  sur le sémaphore sem_busy.
// L'exclusion mutuelle est assurée par le sémaphore sem_critical et par la séparation du thread principal et des threads consommateurs.
// Ici nous avons deux ressources à considérer : les threads consommateurs et le sémaphore sem_busy.
// Pour la détention et attente, le thread principal demande la ressource "fin des threads consommateurs" (ligne 84).
// Pour la détention et attente, les threads consommateurs se détiennent eux-mêmes et demandent la ressource "libération du sémaphore sem_busy" (ligne 38).
// Pour la non-réquisition, seul les threads consommateurs peuvent libérer la ressource associée à eux-mêmes vis-à-vis du thread principal.
// Pour la non-réquisition, aucun thread ne peut libérer le sémaphore sem_busy (ce devrait être fait par le thread principal).
// Attente circulaire : Le thread principal attend la libération des threads consommateurs qui attendent la libération du sémaphore sem_busy (qui devrait être faite par le thread principal). (ligne 84 et 38)