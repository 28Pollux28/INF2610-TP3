#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#define N_THREADS 10

sem_t mutex;

int flag = 0;
int key;

void* is_this_a_deadlock(void * args) {
    sem_wait(&mutex);
    int a = 0, b = 0, c = 0, d = 0;
    int i, j, k, m, n;

    a += 1;
    b += 2;
    c += 3;
    d += 4;
    a -= 1;
    b -= 2;
    c -= 3;
    d -= 4;

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            for (k = 0; k < 5; k++) {
                printf(".");
            }
        }
    }
    printf("\n");

    for (i = 0; i < 10; i++) {
        printf("Loop 1, Iteration: %d\n", i);
    }
    key = rand() % 100;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 5; j++) {
            for (k = 0; k < 3; k++) {
                printf("+");
            }
        }
    }
    printf("\n");

    m = a + b;
    n = c - d;
    a = m + n;
    b = a - n;
    c = b + m;
    d = a + c;

    printf("Hello World 1\n");
    printf("Hello World 2\n");
    printf("Hello World 3\n");

    for (i = 0; i < 10; i++) {
        printf("Another loop: %d\n", i);
        a += i;
        b -= i;
        c += i * 2;
        d -= i * 2;
    }

    if (a > 0) {
        if (key == 17) while(1);
        printf("A is positive\n");
    } else {
        printf("A is not positive\n");
    }

    if (b < 0) {
        printf("B is negative\n");
    } else {
        printf("B is not negative\n");
    }

    printf("This function is long but doesn't do much.\n");
    sem_post(&mutex);
}

int main() {  
    pthread_t threads[N_THREADS];
    sem_init(&mutex, 0, 1); 
    srand(time(NULL));
    
    for(int i = 0; i < N_THREADS; i++){
        pthread_create(&threads[i], NULL, is_this_a_deadlock, NULL);
    }

    for(int i = 0; i < N_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    return 0;
}

// Ici on a un blocage entre les threads si un thread obtient 17 dans la variable key (à la ligne 41).
// Les threads attendent tous la libération de la ressource mutex (ligne 16) pour continuer leur exécution qui est libéré à la fin d'un thread à la ligne 84.
// Seulement si un thread obtient 17 dans la variable key, il va entrer dans une boucle infinie (ligne 71) et ne libérera jamais la ressource mutex.
// Les autres threads vont donc attendre indéfiniment la libération de la ressource mutex par le thread bloqué.
// Pour l'exclusion mutuelle, le sémaphore mutex est utilisé (lignes 16 et 84).
// Ici nous avons une seule ressource à considérer : le sémaphore mutex.
// Pour la détention et attente, un thread détient le mutex et les autres threads attendent la libération de la ressource (ligne 16).
// Pour la non-réquisition, seul le thread qui détient le mutext peut le libérer. (ligne 84)
// Attente circulaire : pas d'attente circulaire ici.
// On ne peut donc pas parler d'interblocage ici, mais d'un blocage simple.
