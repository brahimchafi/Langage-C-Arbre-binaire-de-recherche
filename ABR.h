#include <string.h>

/*---------------------------La structure---------------------------------*/

typedef struct noeud *Pnoeud;

typedef struct type {
    char *tab;
    int freq;

}Type;


typedef struct noeud {
    Type txt;
    Pnoeud fg;
    Pnoeud fd;
} Noeud;

typedef Noeud *ABR;



/*---------------------------Implementation ---------------------------------*/

ABR arbre_vide(){
    return NULL;
}


int est_vide(ABR A){
    return A == NULL;
}


Pnoeud nouveau_noeud(char* t) {
    Pnoeud p = (Pnoeud)malloc(sizeof(Noeud));
        if (p != NULL) {
            Type m;
            m.freq=1;
            m.tab=t;
            p->txt=m;
            p->fg =NULL;
            p->fd =NULL;
        }
        else printf("Echec malloc...Pas assez de memoire !! \n");
    return (p);
}



ABR gauche(ABR A) {
    if (est_vide (A)){
        printf("Erreur : Arbre vide !! \n");
        exit(-1);
    }
    return A->fg;
}



ABR droite(ABR A) {
    if (est_vide (A)){
        printf("Erreur : Arbre vide !! \n");
        exit(-1);
    }
    return A->fd;
}




/*---------------------------Des fonctions---------------------------------*/

void affiche_noeud(Type n){
        printf("%s : %d \n" , n.tab , n.freq);
    }



Type contenu(ABR A){
    if(!est_vide(A))
        return A->txt;
}

char* terme(Type t){
    return t.tab;
}

int freq(Type t){
    return t.freq;
}


void parcours_infixe(ABR A){
  if (A) {
    parcours_infixe(gauche(A));
    affiche_noeud(A->txt);
    parcours_infixe(droite(A));
  }
}


void parcours_prefixe(ABR A){
  if (A) {
    affiche_noeud(A->txt);
    parcours_prefixe(gauche(A));
    parcours_prefixe(droite(A));
  }
}


void parcours_postfixe(ABR A){
  if (A) {
    parcours_postfixe(gauche(A));
    parcours_postfixe(droite(A));
    affiche_noeud(A->txt);
  }
}



ABR ajouter(ABR A, char *t){
  if (est_vide(A)) {
        A = nouveau_noeud(t);
  }
  else {
        int position;
            position=strcmp(t,A->txt.tab);
            if (position==1){
                A->fd = ajouter(A->fd,t);
            }
            if(position==0){
                (A->txt.freq)++;
            }
            if(position==-1){
                A->fg = ajouter(A->fg,t);
            }
        }

        return A;
}


void  affich_par_freq(ABR A){
    if (!est_vide(A)){
            affich_par_freq(gauche(A));
            printf("-%s : %d\n",A->txt.tab,A->txt.freq);
            affich_par_freq(droite(A));
    }
}


ABR ajouter_par_freq(ABR A, Type txt){
    if (est_vide(A)) {
        Pnoeud p = (Pnoeud)malloc(sizeof(Noeud));
        p->txt=txt;
        p->fd=NULL;
        p->fg=NULL;
        A=p;
        return A;
    }
    else {
            if(strcmp(terme(txt),terme(A->txt))){
                if(freq(txt) < freq(contenu(A))){
                    A->fg = ajouter_par_freq(gauche(A),txt);
                }else{
                    A->fd = ajouter_par_freq(droite(A),txt);
                }
            }else{
                (A->txt.freq)++;
            }
            return A;
        }
}

ABR convertir(ABR b,ABR a){
    if (!est_vide(a)){
        b = convertir(b,gauche(a));
        b = ajouter_par_freq(b,contenu(a));
        b = convertir(b,droite(a));
    }
    return b;
}

/*-----------------------------------------------------------------------*/
ABR Reconstruire(ABR A,ABR B){
    Type T;
        T.freq=A->txt.freq;
        printf("1");
        T.tab=A->txt.tab;
        printf("2");
        B=ajouter_par_freq(B,T);
        printf("3");
    B=Reconstruire(A->fg,B);
    printf("4");
    B=Reconstruire(A->fd,B);
    return B;
}



