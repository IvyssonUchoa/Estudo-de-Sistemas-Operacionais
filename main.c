#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex_fork[5];
pthread_t filosofos[5];
int id[5];

void take_fork(int id_filo){ //pega os garfos
  pthread_mutex_lock(&(mutex_fork[id_filo]));
  printf("Filosofo %d pegou os garfos \n", id_filo);

  (id_filo < 4)? pthread_mutex_lock(&(mutex_fork[id_filo + 1])) : pthread_mutex_lock(&(mutex_fork[0]));
}

void drop_fork(int id_filo){
  pthread_mutex_unlock(&(mutex_fork[id_filo]));

  printf("O filosofo %d parou de comer e largou os garfos \n", id_filo);
  (id_filo < 4)? pthread_mutex_unlock(&(mutex_fork[id_filo + 1])) : pthread_mutex_unlock(&(mutex_fork[0]));
}

void* philosopher(void* var){
  int* filo = (int*) var;

  while(1){
    int t_think = (rand()%10 + 2);
    printf("Filósofo %d está pensando\n", *filo);
    sleep(t_think);

    take_fork(*filo); //pega os garfos
    
    int t_eat = (rand()%5 + 1);
    printf("Filósofo %d está comendo\n", *filo);
    sleep(t_eat);

    drop_fork(*filo); //larga dos garfos
  }

  pthread_exit(NULL);
}

int main(){
  for (int f = 0; f < 5; f++){
    pthread_mutex_init(&(mutex_fork[f]), NULL);
  }

  for (int p = 0; p < 5; p++){
    id[p] = p;
    pthread_create(&filosofos[p], NULL, &philosopher,(void *) &id[p]);
  }
  while(1){}
  return 0;
}