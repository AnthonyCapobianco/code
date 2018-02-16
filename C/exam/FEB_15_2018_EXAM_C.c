/*-------------------------------------------------------------------------
IPAM - Annee Academique 2017-2018
Bachelier en Informatique
Cours de Principes Algorithmiques et Programmation
Test Dispensatoire de Decembre 2017
---------------------------------------------------------------------------
Remarque: ce fichier est intentionnellement sans caracteres accentues.
---------------------------------------------------------------------------

Contexte
========
Un nombre parfait est un nombre naturel egal a la somme de ses diviseurs
propres.
Un diviseur propre est un diviseur autre que le nombre lui-meme.
Le premier nombre parfait est 6.
En effet 1, 2 et 3 sont les diviseurs propres de 6 et 1+2+3=6.
28 est egalement un nombre parfait : 1+2+4+7+14=28.
Les nombres parfaits sont rares, il níen existe que trois inferieurs
a 1000 qui sont 6, 28 et 496.
Ensuite vient 8128, puis 33 550 336,
Le philosophe et mathematicien Nicomaque de Gerase (200 apres J.C.)
etudiait les nombres parfaits en les comparant aux nombres deficients
(nombre superieur a la somme de ses diviseurs propres) et aux nombres
abondants (nombre inferieur a la somme de ses diviseurs propres).

Probleme de base (Resolution sine qua non a la reussite)
========================================================
On vous demande d'ecrire le GNS et le code C d'un programme qui, a partir
d'une borne superieure entree au clavier affichera la liste des nombres
naturels allant de 2 a N en precisant pour chacun de ces nombres si ce
dernier est deficient, parfait ou abondant. De plus la somme des
diviseurs propres du nombre considere sera aussi affichee pour verification.

Pour des raisons de lisibilite Le GNS peut etre fait sous l'hypothese (forte)
que l'utilisateur ne se trompe jamais.

Cette hypothese ne tient par contre pas pour le programme C.

Bonus
=====
Sur base du programme de resolution du probleme de base, vous modifierez
votre code C afin que votre programme demande si on desire afficher
seulement
(1) les nombres parfaits
(2) Les nombres deficients et les nombres abondants
(3) tous les nombres.


Bonus Ultime
============
Sur base du programme de resolution du probleme de base, vous modifierez
votre code C afin que votre programme  permette d'afficher n'importe
quelle combinaison de nombres :
(1) les nombres parfaits (oui ou non)
(2) Les nombres deficients (oui ou non)
(3) les nombres abondants (oui ou non)

les choix ci-dessus n'etant pas exclusifs.


-------------------------------------------------------------------------------
CONSIGNES OBLIGATOIRES DE FORMATAGE
-------------------------------------------------------------------------------
Vous realiserez le GNS sur une feuille de papier, alors que vous ecrirez
votre programme C dans ce fichier que vous renommerez en vous conformant
au schema suivant:
NOM_Prenom_PAP_Evaluation_decembre_2017.c

De plus vous indiquerez vos nom et prenom dans l'espace reserve ci-dessous.

Bon travail.
-------------------------------------------------------------------------------
PS: Ne modifiez aucunement les commentaires ci-dessus de ce fichier, merci.
-------------------------------------------------------------------------------

 Nom: CAPOBIANCO

 Prenom: Anthony
-------------------------------------------------------------------------------
Ecrivez votre programme C ci-dessous:
*/
/*
 * Programme qui, a partir d'une borne superieure 
 * affichera la liste des nombres naturels allant de 2 a N  
 * precisant pour chacun de ces nombres si ce dernier est:
 * deficient, parfait ou abondant. 
 * De plus la somme des diviseurs propres du nombre 
 *
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(void) 
{
    int getLimit(char*);
    void printValues(int*);
    
    int bMax = (int) (getLimit("supérieure"));
    printValues(&bMax);
    
    return 0;
}

/* Get the higher limit */
int getLimit(char* string)
{
    char buffer[30];
    char *endPtr;
    
    int result;
    
    do
    {
        printf("Veuillez introduire la borne %s: ", string);
        if (!fgets(buffer, 30, stdin))
        {
            fprintf(stderr, "ERREUR: La valeur introduite est incorrecte\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            buffer[strlen(buffer) - 1] = 0;
            result = strtol(buffer, &endPtr, 10);
        }
    } while (buffer + strlen(buffer) != endPtr);
    
    return(result);
}

void printValues(int *lowLimit)
{
    int i
      , j
      ; 
    int sum;
    
    printf("Les nombres de 2 à %d sont:\n", *lowLimit);
    
    for (i = 2; i <= *lowLimit; ++i, sum = 0)
    {
        for (j = 1; j < *lowLimit; j++) if (!(i %j)) sum += j;
        
        printf("Le nombre %d est %s et la somme de ses diviseur est: %i\n", i
              , ((sum == i) ? "parfait" : (sum < i) ? "déficient" : "abondant"), sum);
    }
}
