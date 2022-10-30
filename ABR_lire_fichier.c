#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ABR.h"

int affiche_Menu(){
    printf("\n");
	printf("|------------------------------------------------Menu-------------------------------------------------|\n");
	printf("|                                                                                                     |\n");
	printf("| 1- Afficher les mot par ordre alphabetique.                                                         |\n");
	printf("|                                                                                                     |\n");
	printf("| 2- Afficher les mot par frequence.                                                                  |\n");
	printf("|                                                                                                     |\n");
	printf("| 3- Ajouter un mot.                                                                                  |\n");
	printf("|                                                                                                     |\n");
	printf("| 4- Supprimer un mot.                                                                                |\n");
	printf("|                                                                                                     |\n");
	printf("| 5- Quitter                                                                                          |\n");
	printf("|                                                                                                     |\n");
	printf("|-----------------------------------------------------------------------------------------------------|\n");
    return choix();
}

int choix(){
    int a ;
    printf("Entrez votre choix >>  ");
    scanf("%d",&a);
    printf("\n");
    return a ;
}


void main(){
        int choix;
        char text[500];
        char* T;
const   char* separators = " ,;:.?!\n";
        FILE* f = fopen("Texte.txt","r");
        fgets(text,500,f);
        ABR A=arbre_vide();
        ABR B=arbre_vide();
        T = strtok ( text, separators );
        while ( T != NULL ) {
            A = ajouter(A,T);
            T = strtok ( NULL, separators );
        }
        B=convertir(B,A);
        printf("L'ajout a partir d'un fichier est effectue avec succes. \n");

        choix = affiche_Menu();
        do{
            switch(choix){
                case 1: parcours_infixe(A);
                    break;

                case 2: affich_par_freq(B);
                    break;

                case 3:{
                    char mot1[25];
                    printf("Entrer le mot a ajouter >> ");
                    scanf("%s",mot1);
                    A = ajouter(A,&mot1);
                    Type mot2;
                    mot2.tab=mot1;
                    mot2.freq=1;
                    B = ajouter_par_freq(B,mot2);
                    printf("\nVotre mot a ete ajoute avec succes. \n\n"); }
                    break;

                case 4: printf("\nSORRY !!, Vous n'avez pas le droit de supprimer. \n");
                    break;

                case 5: exit(-1);
                break;
            }
            choix = affiche_Menu();
         }while(choix !=0);


}
