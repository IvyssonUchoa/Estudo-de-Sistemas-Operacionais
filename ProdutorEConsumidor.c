#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX 1000000000
pthread_mutex_t the_mutex;
pthread_cond_t condc, condp;
int buffer[10] = {};

const clock_t MAXDELAY = 1000000;

void delay(clock_t ticks) {
  clock_t start = clock();
  do
    ; while (clock() < start + ticks);
}

void *producer(void *ptr) {
    for (int j = 1, i = 1; i <= MAX; j++, i++) {
        if (j > 10) j = 1;

        pthread_mutex_lock(&the_mutex);
      
        while (buffer[j-1] != 0)
            // Pode acabar a fatia de tempo?
            pthread_cond_wait(&condp, &the_mutex);
      
        printf("\nColocando item %d no buffer", i);
        buffer[j-1] = i; /*coloca item no buffer */     
        delay(MAXDELAY);

        pthread_cond_signal(&condc); /* acorda consumidor */
        pthread_mutex_unlock(&the_mutex);/* libera acesso ao buffer */
    }
    pthread_exit(0);
}

void *consumer(void *ptr) {
    for (int j = 1, i = 1; i <= MAX; i++, j++) {
        if (j > 10) j = 1;

        pthread_mutex_lock(&the_mutex); 

        while (buffer[j-1] == 0) pthread_cond_wait(&condc, &the_mutex);
      
        printf("\nRetirando item %d no buffer", i);
        buffer[j-1] = 0; /* retira o item do buffer */
        delay(MAXDELAY);

        pthread_cond_signal(&condp);
        pthread_mutex_unlock(&the_mutex);/* libera acesso ao buffer */
    }
    pthread_exit(0);
}

int main(int argc, char **argv)
{
    pthread_t pro, con;
    pthread_mutex_init(&the_mutex, 0);
    pthread_cond_init(&condc, 0);
    pthread_cond_init(&condp, 0);
    pthread_create(&con, 0, consumer, 0);
    pthread_create(&pro, 0, producer, 0);
    pthread_join(pro, 0);
    pthread_join(con, 0);
    pthread_cond_destroy(&condc);
    pthread_cond_destroy(&condp);
    pthread_mutex_destroy(&the_mutex);
}