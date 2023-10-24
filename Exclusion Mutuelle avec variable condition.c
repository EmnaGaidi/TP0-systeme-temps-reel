#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct { //déclaration du type de la donnée partagée
float taille;
float poids;
} type_donneePartagee;

pthread_mutex_t verrou; //déclaration du verrou
pthread_cond_t cond = PTHREAD_COND_INITIALIZER; //initialisation de la variablecondition
type_donneePartagee donneePartagee; //déclaration de la donnée partagée

void* tache1(void *arg){ // déclaration du corps de la tâche qui lit la donnée partagée. Onconsidère qu'elle s'exécute indéfiniment
type_donneePartagee ma_donneePartagee;
int i=0;
while(i<10){
        pthread_mutex_lock(&verrou);
        pthread_cond_wait(&cond, &verrou); // La fonction permettant d'endormir une tâche (possédant le verrou sur la donnée partagée) si la condition cond est fausse
        ma_donneePartagee = donneePartagee;
        pthread_mutex_unlock(&verrou);
        printf("La tache %s vient de lire la donnee partagee\n", (char*) arg);
        //utilisation de ma_donneePartagee
        usleep(1000000);
        i++;
}
}

void* tache2(void *arg){ // déclaration du corps de la tâche qui modifie la donnée partagée.On considère qu'elle s'exécute indéfiniment
int i=0;
while(i<10){
        pthread_mutex_lock(&verrou);
        donneePartagee.taille = 100 + rand()%101; //choisir une taille au hasard entre 100 et200cm. // Dans un programme réel, les données à modifier peuvent provenir de capteurs etnécessitent un code un peu plus complexe
        donneePartagee.poids = 10 + rand()%101;
        if(donneePartagee.taille >= 120 && donneePartagee.poids >= 60){
                pthread_cond_signal(&cond); //La fonction permettant de rendre la condition cond vraie. Cela envoie un signal de réveil aux tâches qui ont été endormies sur cette condition
        }pthread_mutex_unlock(&verrou);
        printf("La tache %s vient de modifier la donnee partagee\n", (char*) arg);
        usleep(1000000);
        i++;
}
}

int main(void)
{
srand(200);
pthread_t th1, th2;
pthread_mutex_init(&verrou, NULL);
//initialisation de la donnée partagée
donneePartagee.taille = 100 + rand()%101;
donneePartagee.poids = 10 + rand()%101;
pthread_create(&th1, NULL, tache1, "1");
pthread_create(&th2, NULL, tache2, "2");
pthread_join(th1, NULL);
pthread_join(th2, NULL);
return 0;
}
