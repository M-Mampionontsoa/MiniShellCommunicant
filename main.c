#include "ProgrammePrincipal.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <pthread.h>

int main(int argc,char *argv[])
{
    pthread_t thread_surveillance;

    // Créer un thread de fond au lancement
    if(pthread_create(&thread_surveillance, NULL, displayRessource, NULL) != 0) {
        perror("Erreur thread de surveillance");
        exit(EXIT_FAILURE);
    }

    // Boucle du menu principal
    while(1)
    {
        menu();
        printf("\n");
    }

    return 0;
}
