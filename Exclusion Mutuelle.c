#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct { // d�claration du type de la donn�e partag�e
float taille;
float poids;
} type_donneePartagee;

pthread_mutex_t verrou; //d�claration du verrou
type_donneePartagee donneePartagee; //d�claration de la donn�e partag�e

void* tache1(void *arg){ // d�claration du corps de la t�che qui lit la donn�e partag�e. Onconsid�re qu'elle s'ex�cute ind�finiment
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

void* tache2(void *arg){ // d�claration du corps de la t�che qui modifie la donn�e partag�e.On consid�re qu'elle s'ex�cute ind�finiment
int i=0;
while(i<10){
        pthread_mutex_lock(&verrou);
        donneePartagee.taille = 100 + rand()%101; //choisir une taille au hasard entre 100 et200cm. // Dans un programme r�el, les donn�es � modifier peuvent provenir de capteurs etn�cessitent un code un peu plus complexe
        donneePartagee.poids = 10 + rand()%101;
        pthread_mutex_unlock(&verrou);
        printf("La tache %s vient de modifier la donnee partagee\n", (char*) arg);
        usleep(1000000);
        i++;
}

}
int main(void)
{
srand(200);// elle initialise le g�n�rateur de nombres pseudo-al�atoires avec une valeur de d�part de 200
// vous initialisez le g�n�rateur de nombres pseudo-al�atoires avec la graine (seed) 200. Si vous appelez ensuite des fonctions comme rand() pour g�n�rer des nombres al�atoires, vous obtiendrez toujours la m�me s�quence de nombres pseudo-al�atoires � chaque ex�cution du programme, car la graine est fix�e � 200
pthread_t th1, th2;
pthread_mutex_init(&verrou, NULL);
// le param�tre NULL est utilis� pour sp�cifier que l'on souhaite utiliser les attributs par d�faut pour initialiser un verrou (mutex) en utilisant la configuration standard d�finie par le syst�me d'exploitation.
//initialisation de la donn�e partag�e
donneePartagee.taille = 100 + rand()%101;
donneePartagee.poids = 10 + rand()%101;
pthread_create(&th1, NULL, tache1, "1");
pthread_create(&th2, NULL, tache2, "2");
pthread_join(th1, NULL);
pthread_join(th2, NULL);
return 0;
}
