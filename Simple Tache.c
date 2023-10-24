#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
void* fonc(void* arg){
int i;
for(i=0;i<7;i++){
printf("Tache %d : %d\n", (int) arg, i);
usleep(1000000); //attendre 1 seconde
}
}
int main(void)
{
pthread_t tache1, tache2; //d�claration des deux t�ches
pthread_create(&tache1, NULL, fonc, (void*) 1); //cr�ation effective de la t�che tache1
pthread_create(&tache2, NULL, fonc, (void*) 2);
pthread_join(tache1, NULL); //la fonction principale main(void), doit attendre la fin de l'ex�cution de la t�che tache1
pthread_join(tache2, NULL); // doit atteindre la fin de l'ex�cution de la tache tache2
return 0;
}
