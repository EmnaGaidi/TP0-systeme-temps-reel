#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct { //d�claration du type de la donn�e partag�e
float taille;
float poids;
} type_donneePartagee;

pthread_mutex_t verrou; //d�claration du verrou
pthread_cond_t cond = PTHREAD_COND_INITIALIZER; //initialisation de la variablecondition
type_donneePartagee donneePartagee; //d�claration de la donn�e partag�e

void* tache1(void *arg){ // d�claration du corps de la t�che qui lit la donn�e partag�e. Onconsid�re qu'elle s'ex�cute ind�finiment
type_donneePartagee ma_donneePartagee;
int i=0;
while(i<10){
        pthread_mutex_lock(&verrou);
        pthread_cond_wait(&cond, &verrou); // La fonction permettant d'endormir une t�che (poss�dant le verrou sur la donn�e partag�e) si la condition cond est fausse
        ma_donneePartagee = donneePartagee;
        pthread_mutex_unlock(&verrou);
        printf("La tache %s vient de lire la donnee partagee\n", (char*) arg);
        //utilisation de ma_donneePartagee
        usleep(1000000);
        i++;
}
}

void* tache2(void *arg){ // d�claration du corps de la t�che qui modifie la donn�e partag�e.On consid�re qu'elle s'ex�cute ind�finiment
int i=0;
while(i<10){
        pthread_mutex_lock(&verrou);
        donneePartagee.taille = 100 + rand()%101; //choisir une taille au hasard entre 100 et200cm. // Dans un programme r�el, les donn�es � modifier peuvent provenir de capteurs etn�cessitent un code un peu plus complexe
        donneePartagee.poids = 10 + rand()%101;
        if(donneePartagee.taille >= 120 && donneePartagee.poids >= 60){
                pthread_cond_signal(&cond); //La fonction permettant de rendre la condition cond vraie. Cela envoie un signal de r�veil aux t�ches qui ont �t� endormies sur cette condition
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
//initialisation de la donn�e partag�e
donneePartagee.taille = 100 + rand()%101;
donneePartagee.poids = 10 + rand()%101;
pthread_create(&th1, NULL, tache1, "1");
pthread_create(&th2, NULL, tache2, "2");
pthread_join(th1, NULL);
pthread_join(th2, NULL);
return 0;
}
