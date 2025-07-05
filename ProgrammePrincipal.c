#include "ProgrammePrincipal.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <pthread.h>

extern char **environ;
void varEvenGestion()
{
    int choice = 0;
    int i=0;
    printf("\t===Gestion des variables d'envrinnemnt===\n");
    printf("*1-Voir tous les listes des variables d'environnement à l'instant t\n");
    printf("*2-Modifier la liste des variables d'environnemnt*\n");
    
    scanf("%d",&choice);

    switch(choice)
    {
        case 1:
            for(i=0;environ[i] != NULL;i++)
            {
                printf("environ[%d]:%s\n",i,environ[i]);
            }
        break;

        case 2:
            for(i=0;environ[i] != NULL;i++)
            {
                char update[750];
                char *path;
                int choix;
                char *newPath=malloc(5000);
                    
                printf("Ajouter un nouveau variable d'environnement(taper 1) ou modifier un variable existant:(taper 2)");
                scanf("%d",&choix);
                if(choix == 1)
                {
                    char nouveau[500];
                    printf("Entrer son nom et sa valeur(Format comme ceci NOM=VALEUR):");
                    scanf("%s",nouveau);
                    putenv(nouveau);
                }
                else if(choix == 2)
                {
                    char nom[300];
                    printf("Entrer le nom du variable à modifier:");
                    scanf("%s",nom);
                    printf("Entrer le chemin absolue de votre repertoire à ajouter au variable d'environnement:");
                    scanf("%s",update);
                    path=getenv(nom);
                    snprintf(newPath,5000,"PATH=%s:%s",path,update);
                    putenv(newPath);
                    printf("Variable ajouter avec succes\n");
                    menu();
                }

                else
                {
                    while(choix != 1 && choix !=2)
                    {
                        printf("Ajouter un nouveau variable d'environnement(taper 1) ou modifier un variable existant:(taper 0):");
                        scanf("%d",&choix);
                    }
                }
                
                
            }
        break;

        default:
            while(choice != 1 &&choice !=2)
            {
                printf("Entrer 1 ou 2:");
                scanf("%d\n",&choice);
            }
            

    }
}

void execOtherProgram()
{
    int fils=0;
    int tube[2];
    char file[200];
    
    if(pipe(tube) != 0)
    {
        perror("Erreur lors de la création du tube\n");
        exit(1);
    }


    switch(fils = fork())
    {
        case -1:

            printf("Erreur lors de la création du processus fils\n");
            exit(1);

        break;

        case 0:

            char buffer[500];
            char *arg[10];
            int i=0;
            char *token;
            close(tube[1]);
            read(tube[0],buffer,sizeof(buffer));  
            token = strtok(buffer," ");
            while(token != NULL && i<9)
            {
                arg[i]=token;
                token=strtok(NULL," ");
                i++;
            }
            arg[i]=NULL;
            snprintf(file,sizeof(file),"/usr/bin/%s",arg[0]);
            execvp(file,arg);
            close(tube[0]);
            
           
        break;


        default:

            char cmd[500];   
            printf("Entrer des commandes courants:\n");
            printf("usr@usr~$");
            scanf("%499[^\n]",cmd);
            close(tube[0]);
            write(tube[1],cmd,sizeof(cmd));
            close(tube[1]);
            wait(NULL);
            

        break;
            

    }
    
}

void processuCommunication()
{
    char programme1[100];
    char programme2[100];
    char *exec1;
    char *exec2;
    char *cmd;
    printf("Entrer les noms des deux programes que vous voulez faire communiquer(Fichier executable):");
    scanf("%s",programme1);
    scanf("%s",programme2);
    asprintf(&exec1,"./%s",programme1);
    asprintf(&exec2,"./%s",programme2);
    asprintf(&cmd,"%s & %s",exec1,exec2);
    system(cmd);
    free(exec1);
    free(exec2);
    free(cmd);
    
    
}

void *displayRessource(void *arg)
{
    while(1)
    {
        //int pid = getpid();
        printf("\n\nProcessus en cours PID=%d\n",getpid());
        printf("\nCaractéristique de votre mémoire vive en temps réels:\n");
        system("free -m | head -2");
        printf("Caractéristique de votre cpu en temps réels:\n");
        system("cat /proc/loadavg");
        printf("\n\n");
        sleep(10);

    }

    return NULL;
    

}

void menu()
{

   int choix;
   printf( "\t=== Mini Shell Communicant ===\n");
   printf("1. Gestion des variables d’environnement\n");
   printf("2. Lancer une commande externe (ls, date, etc.)\n");
   printf("3. Communiquer avec un programme via tube nommé\n");
   printf("0. Quitter\n");
   printf("Choix :");

   scanf("%d",&choix);
   while (getchar() != '\n');

   switch(choix)
   {
        case 1:
        
        varEvenGestion();
        break;

        case 2:
            
            execOtherProgram();
                
            
            
        break;

        case 3:
            processuCommunication();
        break;

        case 0:
            exit(1);
        break;

        default:
            while (scanf("%d", &choix) != 1 || choix < 0 || choix > 3) 
            {
                printf("Choix invalide. Entrer un nombre entre 0 et 3 : ");
                while (getchar() != '\n'); 
            }
        break;
   }

}
