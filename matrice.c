
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N 10 // places dans le buffer
#define n1 10
#define m1 10
#define n2 10
#define m2 10

// Matrices globales
int B[n1][m1];
int C[n2][m2];
int A[n1][m2];

// Tampon
int T[N];

// Synchronisation
pthread_mutex_t mutex;
sem_t empty;
sem_t full;

// Fonctions non définies dans ce contexte
int produce(int item);
void insert_item(int item);
int remove_item(void);

// Producteur
void *producer(void *arg)
{
    int item;
    // Pour chaque ligne
    for (int i = 0; i < n1; ++i)
    {
        item = produce(item);
        sem_wait(&empty); // Attente d'une place libre
        pthread_mutex_lock(&mutex);
        // Section critique
        insert_item(item);
        pthread_mutex_unlock(&mutex);
        sem_post(&full); // Il y a une place remplie en plus
    }
    pthread_exit(NULL);
}

// Consommateur
void *consumer(void *arg)
{
    int item;
    while (1)
    {
        sem_wait(&full); // Attente d'une place remplie
        pthread_mutex_lock(&mutex);
        // Section critique
        item = remove_item();
        pthread_mutex_unlock(&mutex);
        sem_post(&empty); // Il y a une place libre en plus
    }
    pthread_exit(NULL);
}

int main()
{
    // Initialisation
    sem_init(&empty, 0, N); // Buffer vide
    sem_init(&full, 0, 0);  // Buffer vide
    pthread_mutex_init(&mutex, NULL); // Exclusion mutuelle

    // Création des threads
    pthread_t producer_thread, consumer_thread;

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Attente des threads
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Destruction
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
