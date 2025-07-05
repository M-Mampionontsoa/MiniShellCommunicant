#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    const char *fifo = "/tmp/mon_tube";
    int fd;

    // Créer le tube nommé s'il n'existe pas
    if (mkfifo(fifo, 0666) == -1 && errno != EEXIST) {
        perror("Erreur lors de la création du tube nommé");
        return 1;
    }

    // Ouvrir le tube en mode écriture
    printf("Écrivain : en attente d'un lecteur...\n");
    fd = open(fifo, O_WRONLY);
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du tube");
        return 1;
    }

    // Écrire un message
    char *message = "Salut depuis l'écrivain!";
    write(fd, message, strlen(message) + 1); // Inclut le \0
    printf("Écrivain : message envoyé\n");

    // Fermer le tube
    close(fd);
    return 0;
}