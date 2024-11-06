#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_THREADS 5
#define MAX_ROUNDS 3

pthread_mutex_t locks[NUM_THREADS];

void* cons(void* arg) {
    int id = *(int*)arg;
    int rounds = 0;

    while (rounds < MAX_ROUNDS) {
        sleep(1);
        int left = id;
        int right = (id + 1) % NUM_THREADS;
        
        pthread_mutex_lock(&locks[left]);
        sleep(1);
        pthread_mutex_lock(&locks[right]);

        sleep(1);
        rounds++;
        pthread_mutex_unlock(&locks[left]);
        pthread_mutex_unlock(&locks[right]);
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_mutex_init(&locks[i], NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, cons, &ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

// Le programme est dans une situation d'interblocage causée par les threads qui attendent des verrous détenus par des threads voisins.
// Exclusion mutuelle : Les ressources disponibles sont les verrous (locks) et les threads demandent et détiennent les verrous (lignes 19 et 21).
// Détention et attente : Les threads détiennent le verrou de gauche et demandent le verrou de droite (lignes 19 et 21).
// Non-réquisition : Seuls les threads qui possèdent un verrou peuvent le libérer (lignes 25 et 26).
// Attente circulaire : Les threads détiennent tous leur verrou de gauche et attendent le verrou de droite détenu par leur voisin (lignes 19 et 21).
// Il y a donc une situation d'interblocage.