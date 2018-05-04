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
Les nombres parfaits sont rares, il n’en existe que trois inferieurs
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
#include <stdio.h>
#include <string.h>

#define iIs "%i est %s\n",i,
int main(void)
{
    int  max
        ,sum = 0
        ;
    int  i // itterator
        ,d // devisor
        ,v // check if scanf is valid
        ;
    char  par[] = "parfait"
         ,def[] = "deficient"
         ,abo[] = "abondant"
         ;
    int   uP = 0 // bool show par string
         ,uD = 0 // bool show def string
         ,uA = 0 // bool show abo string
         ;
    char  answer[3];

    printf("Ce programme affiche les numbre deficient, parfait ou abondant.\n");
    printf("Veillez introduire un nombre entier positif comme borne superieur: ");
    v = scanf("%i",&max);

    {// bonus ultime
        printf("Voulez-vous afficher:\n");
        printf("\tLes nombres parfaits (oui ou non): ");
        v = scanf("%s", answer);
        if(!strcmp(answer, "oui") && v) uP = 1;
        answer[0] = 0;

        printf("\tLes nombres deficients (oui ou non): ");
        v = scanf("%s", answer);
        if(!strcmp(answer, "oui") && v) uD = 1;
        answer[0] = 0;

        printf("\tLes nombres abondants (oui ou non): ");
        v = scanf("%s", answer);
        if(!strcmp(answer, "oui") && v) uA = 1;
    }
    
    // find if perfect deficient or abondant
    if(v)
    {
        for(i = 2; i <= max; ++i )
        {
            for(d = 1, sum = 0; d < i; ++d )
            {
                if (i %d == 0) sum += d;
            }// for(d < i)

            if (sum == i && uP) printf(iIs par);
            else if (sum < i && uD) printf(iIs def);
            else if (sum > i && uA) printf(iIs abo);
        }// for(i <= max)
    }// if(v)

    return 0;
}
