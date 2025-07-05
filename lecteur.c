#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    const char *fifo = "/tmp/mon_tube";
    int fd;
    char buffer[100];

    // Ouvrir le tube en mode lecture
    printf("Lecteur : en attente de données...\n");
    fd = open(fifo, O_RDONLY);
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du tube");
        return 1;
    }

    // Lire le message
    read(fd, buffer, sizeof(buffer));
    printf("Lecteur : message reçu : %s\n", buffer);

    // Fermer le tube
    close(fd);

    // Supprimer le tube nommé (facultatif)
    unlink(fifo);
    return 0;
}