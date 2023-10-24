#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct { // déclaration du type de la donnée partagée
float taille;
float poids;
} type_donneePartagee;

pthread_mutex_t verrou; //déclaration du verrou
type_donneePartagee donneePartagee; //déclaration de la donnée partagée

void* tache1(void *arg){ // déclaration du corps de la tâche qui lit la donnée partagée. Onconsidère qu'elle s'exécute indéfiniment
type_donneePartagee ma_donneePartagee;
int i=0;
while(i<10){
        pthread_mutex_lock(&verrou);
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
        pthread_mutex_unlock(&verrou);
        printf("La tache %s vient de modifier la donnee partagee\n", (char*) arg);
        usleep(1000000);
        i++;
}

}
int main(void)
{
srand(200);// elle initialise le générateur de nombres pseudo-aléatoires avec une valeur de départ de 200
// vous initialisez le générateur de nombres pseudo-aléatoires avec la graine (seed) 200. Si vous appelez ensuite des fonctions comme rand() pour générer des nombres aléatoires, vous obtiendrez toujours la même séquence de nombres pseudo-aléatoires à chaque exécution du programme, car la graine est fixée à 200
pthread_t th1, th2;
pthread_mutex_init(&verrou, NULL);
// le paramètre NULL est utilisé pour spécifier que l'on souhaite utiliser les attributs par défaut pour initialiser un verrou (mutex) en utilisant la configuration standard définie par le système d'exploitation.
//initialisation de la donnée partagée
donneePartagee.taille = 100 + rand()%101;
donneePartagee.poids = 10 + rand()%101;
pthread_create(&th1, NULL, tache1, "1");
pthread_create(&th2, NULL, tache2, "2");
pthread_join(th1, NULL);
pthread_join(th2, NULL);
return 0;
}
