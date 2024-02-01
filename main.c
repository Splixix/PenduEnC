#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define TAILLE_MAX 100
#define ESSAIS_MAX 8

// Fonction pour afficher le pendu en fonction du nombre d'essais restants
void printPendu(int essais)
{

    switch (essais)
    {
    case 8:
        printf("\n\n\n\n\n\n\n\n\n");
        break;
    case 7:
        printf("\n\n\n\n\n\n\n\n|\n|_______\n");
        break;
    case 6:
        printf("\n\n\n\n\n\n\n\n|\n|\n|\n|_______\n");
        break;
    case 5:
        printf("\n\n\n\n\n|\n|\n|\n|\n|\n|\n|_______\n");
        break;
    case 4:
        printf("\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|_______\n");
        break;
    case 3:
        printf("__\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|_______\n");
        break;
    case 2:
        printf("_________\n|       |      \n|       |      \n|      / \\     \n|      \\_/     \n|              \n|              \n|              \n|              \n|              \n|              \n|_______\n");
        break;
    case 1:
        printf("_________\n|       |      \n|       |      \n|      / \\     \n|      \\_/     \n|       |     \n|      /|\\    \n|     / | \\   \n|              \n|              \n|              \n|_______\n");
        break;
    case 0:
        printf("_________\n|       |      \n|       |      \n|      / \\     \n|      \\_/     \n|       |     \n|      /|\\    \n|     / | \\   \n|       |      \n|      / \\     \n|     /   \\    \n|_______\n");;
        break;



    default:
        printf("Perdu gros looser !\n");
    }
}
int main()
{




    int jouer = 1;
    while(jouer != 0)
    {
        // Ouvre le fichier des scores en mode ajout
        FILE *scoresFile = fopen("scores.txt", "a+");
        if (scoresFile == NULL)
        {
            fprintf(stderr, "Impossible d'ouvrir le fichier scores.txt.\n");
            return 1;
        }
        // Autres initialisations et ouverture du fichier de mots
        int crampte = 0;
        FILE *file = fopen("C:\\Users\\coren\\Downloads\\Projet Métier - INFDIET2 - Algorithme et Programmation\\words.txt", "r");
        if (file == NULL)
        {
            fprintf(stderr, "Impossible d'ouvrir le fichier words.txt.\n");
            return 1;
        }
        //partie permettant d'avoir un mot aléatoire dans la liste
        char mots[1000][TAILLE_MAX];
        int numMots = 0;

        while (fgets(mots[numMots], TAILLE_MAX, file) != NULL)
        {
            int longueur = strlen(mots[numMots]);
            if (mots[numMots][longueur - 1] == '\n')
                mots[numMots][longueur - 1] = '\0';

            numMots++;
        }

        fclose(file);

        srand(time(NULL));

        int randomIndex = rand() % numMots;
        char *motChoisi = mots[randomIndex];

        //stockage du mot dans des variables et anonymisation
        int tailleMot = strlen(motChoisi);
        char *motCache = (char *)malloc((tailleMot + 1) * sizeof(char));
        memset(motCache, '_', tailleMot);
        motCache[tailleMot] = '\0';
        printf(motChoisi);
        printf(motCache);
        printf("\n");

        //initialisation des compteurs de fautes
        int essaisRestant = ESSAIS_MAX;
        char lettresTrouves[TAILLE_MAX] = "";
        int compteurLettresTrouve = 0;

        //demande de nom du joueur
        char nomJoueur[TAILLE_MAX];
        printf("Entrez votre nom : ");
        scanf("%s", nomJoueur);
        printf("Bonjour %s ! Essayez de deviner le mot.\n", nomJoueur);
        int score = 0;
        char ligne[TAILLE_MAX];
        while (fgets(ligne, TAILLE_MAX, scoresFile) != NULL)
        {
            char nom[TAILLE_MAX];
            int ancienScore;
            if (sscanf(ligne, "%s %d", nom, &ancienScore) == 2 && strcmp(nom, nomJoueur) == 0)
            {
                score = ancienScore;
                break;
            }
        }

        while (essaisRestant >= 0)
        {
            // Affichage du mot actuel, lettres proposées, et tentatives restantes
            printf("\nMot actuel : %s\n", motCache);
            printf("Lettres deja proposees : %s\n", lettresTrouves);
            printf("Tentatives restantes : %d\n", essaisRestant);

            // Appel de la fonction pour afficher le pendu
            printPendu(essaisRestant);

            //Boucle pour demander au joueur un charactère et verification
            //que c'est une lettre de l'alphabet
            int check = 0;
            char lettreTrouve;
            while(check==0)
            {
                printf("Entrez une lettre : ");
                scanf(" %c", &lettreTrouve);
                if(isalpha(lettreTrouve)!=0)
                {
                    if(islower(lettreTrouve)!=0)
                    {
                        check++;
                    }
                    else
                    {
                        lettreTrouve=tolower(lettreTrouve);
                        check++;
                    }
                }
                else
                {
                    printf("Caractere invalide, veuillez saisir de nouveau\n");
                }
            }


            // Vérification si la lettre a déjà été proposée
            int dejaTrouve = 0;
            for (int i = 0; i < compteurLettresTrouve; i++)
            {
                if (lettresTrouves[i] == lettreTrouve)
                {
                    dejaTrouve = 1;
                    printf("Vous avez deja propose cette lettre. Veuillez en choisir une autre.\n");
                    break;
                }
            }

            if (!dejaTrouve)
            {
                lettresTrouves[compteurLettresTrouve++] = lettreTrouve;
                lettresTrouves[compteurLettresTrouve] = '\0';

                int trouve = 0;
                for (int i = 0; i < tailleMot; i++)
                {
                    if (motChoisi[i] == lettreTrouve)
                    {
                        motCache[i] = lettreTrouve;
                        trouve = 1;
                        crampte++;
                    }
                }

                if (!trouve)
                {
                    essaisRestant--;
                    printf("La lettre n'est pas dans le mot.\n");
                }
                else
                {
                    printf("Bonne devinette !\n");
                }
            }
            if (crampte == tailleMot)
            {
                break;
            }
        }


        // Vérification si le joueur a trouvé toutes les lettres du mot
        // Sortie de la boucle si le mot a été trouvé ou si les essais sont épuisés
        printf("\nMot cache : %s\n", motChoisi);
        if (essaisRestant <= 0)
        {
            printf("Desole, vous avez epuise toutes vos tentatives. Le pendu est complet.\n");
        }

        else
        {
            if(crampte==tailleMot)
            {
                printf("Felicitations ! Vous avez trouve le mot.\n");
            }
            else
            {
                printf("erreur code");
            }
        }
        score++;

        // Mise à jour du score & du fichier des scores
        fseek(scoresFile, 0, SEEK_SET);
        int trouvee = 0;
        FILE *tempFile = fopen("temp.txt", "w");
        while (fgets(ligne, TAILLE_MAX, scoresFile) != NULL)
        {
            char nom[TAILLE_MAX];
            int ancienScore;
            if (sscanf(ligne, "%s %d", nom, &ancienScore) == 2 && strcmp(nom, nomJoueur) == 0)
            {
                fprintf(tempFile, "%s %d\n", nom, score);
                trouvee = 1;
            }
            else
            {
                fprintf(tempFile, "%s %d\n", nom, ancienScore);
            }
        }


        if (!trouvee)
        {
            fprintf(tempFile, "%s %d\n", nomJoueur, score);
        }

        fclose(scoresFile);
        fclose(tempFile);
        remove("scores.txt");
        rename("temp.txt", "scores.txt");

        // Libération de la mémoire allouée pour le mot caché
        free(motCache);
        printf("voulez vous continuer a jouer ?  oui=1  |  non=0 \n");
        scanf("%d", &jouer);


    }
    // Affiche le fichier des scores
    system("cmd /c C:/Users/coren/Documents/CodeBlock/PenduFinal/scores.txt");
    return 0;
}
