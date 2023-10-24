#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* fonc(void* arg){
int i;
for(i=0;i<7;i++){
printf("Tache %d : %d\n", (int) arg, i);
usleep(1000000);
}
}

int main(void)
{
pthread_t tache1, tache2;
pthread_attr_t attr; // Déclaration de variables des propriétés.
struct sched_param param; //La déclaration de la structure de données Posix utilisée pour affecter une priorité à la tâche à créer

pthread_attr_init(&attr); // Initialisation de attr aux valeurs par défaut (obligatoire).
param.sched_priority = 12;
pthread_setschedparam(pthread_self(), SCHED_FIFO, &param); //pthread_self() pointe sur le processus en cours d'exécution, à l'occurrence la fonction main()
//le processus main() sera ordonnancé en SHED_FIFO avec une priorité de 12

pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED); // la tâche à créer sera forcée d'utiliser les paramètres
//d'ordonnancement contenus dans sa propriété attr ;
pthread_attr_setschedpolicy(&attr, SCHED_FIFO);

param.sched_priority = 12;
pthread_attr_setschedparam(&attr, &param); // La fonction qui permet d'affecter à la propriété attr de la tâche à créer, sa priorité (qui est
//un nombre entier) contenue dans la variable param
pthread_create(&tache1, &attr, fonc, 1); // la tâche tache1 créée, sera ordonnancée en SHED_FIFO avec une priorité de 10

param.sched_priority = 7;
pthread_attr_setschedparam(&attr, &param);
pthread_create(&tache2, &attr, fonc, 2); // la tâche tache2 créée, sera ordonnancée en SHED_FIFO avec une priorité de 7
pthread_attr_destroy(&attr);
pthread_join(tache1, NULL);
pthread_join(tache2, NULL);
return 0;
}
