#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t evt; //d�claration du s�maphore repr�sentant l'�v�nement de synchronisation

void* tache1(void *arg){
int i=0;
while(i<10){
        printf("La tache %s s'execute\n", (char*) arg);
        //suite du code
        sem_post(&evt); //la t�che 1 �met l'�v�nement � la fin de son ex�cution
        i++;
}
}

void* tache2(void *arg){
int i=0;
while(i<10){
        sem_wait(&evt); //la t�che 2 est bloqu�e en attente de l'�mission de l'�v�nement qui luipermettra de poursuivre
        printf("La tache %s s'execute enfin\n", (char*) arg);
        //suite du code
        i++;
}
}

int main()
{
pthread_t th1, th2;
sem_init(&evt, 0, 2); // le s�maphore est local au processus issu de la fonction main() et aun compteur initialis� a 2
pthread_create(&th1, NULL, tache1, "1");
pthread_create(&th2, NULL, tache2, "2");
pthread_join(th1, NULL);
pthread_join(th2, NULL);
return 0;
}
