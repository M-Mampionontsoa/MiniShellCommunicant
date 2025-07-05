#include <stdlib.h>

/*Fonction qui va afficher le menu infiniment jusqu'à ce qu'on arrête
*/
void menu();

/*Fonction gérant les variables d'environnement*/
void varEvenGestion();

/*Fonction qui va appeler les autres programmes pour la 
communication entre processus*/
void execOtherProgram();

/*Fonction qui va executer des autres programmes de votre choix 
pour la communication d'un processus*/
void processuCommunication();
/*cette fonctionnalité de communication entre processus suppose que vous avez
dans votre repertoire des programmes qui vont communiquer */

/*Fonction qui va être executé en arrière plan pour voir l'évolution
des ressources machine*/
void *displayRessource(void *arg);

/*Fonction qui va gérer la création l'execution et la gestion des threads
qui s'éxecute en arrière plan*/
void execBackground();
