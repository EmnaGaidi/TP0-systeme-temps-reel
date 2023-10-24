#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

void* tachePeridique(void* periode){
pthread_cond_t cond;
pthread_mutex_t verrou;
struct timespec time; // declaration de la structure de donn�es de gestion du temps

pthread_cond_init(&cond, NULL);
pthread_mutex_init(&verrou, NULL);

int i=0;
clock_gettime(CLOCK_REALTIME, &time); // La fonction permettant de r�cup�rer le temps de l'horloge du syst�me
while(i<10){
pthread_mutex_lock(&verrou);
time.tv_sec = time.tv_sec + (int) periode;
printf("La tache %s s'execute periodiquement � l'instant %d secondes\n", "t1", (int)time.tv_sec);
//suite du code
// Cette fonction utilise un d�compteur (timeout) sur le temps time pour r�veiller la t�che
//endormie sur l'attente de la variable condition cond qui ne sera jamais signal�e.
pthread_cond_timedwait(&cond, &verrou, &time);
pthread_mutex_unlock(&verrou);
i++;
}
}

int main(void)
{
pthread_t tache1;
pthread_create(&tache1, NULL, tachePeridique, (void*) 5); //la tache1 est p�riodique deperiode 5s
pthread_join(tache1, NULL);
return 0;
}
