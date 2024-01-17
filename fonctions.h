#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct ville{
// la structure ville qui contient 3 paramètres: le nom de la ville, le nombre de trajets qui passe par la ville et le nombre de fois que la ville est ville de départ d'une étape
	char nom[1000];
	int nbtrajet;
	int nbdep;
}Ville;

typedef struct top{
// la structure top qui contient les 10 villes qui ont le plus de trajets
	Ville* tab;
}Top;
	
typedef struct arbre{
// la structure pour l'AVL
	Ville* elmt;
	int eq;
	struct arbre * fg;
	struct arbre * fd;
}Arbre;

typedef Arbre * pArbre;	

typedef struct trajet{
// la structure trajet qui contient 4 paramètres: l'id du trajet, la moyenne des distances du trajet, la distance maximale d'étape du trajet et la distance minimale d'étape du trajet
	int id;
	float moy;
	int max;
	int min
}Trajet;

typedef struct top2{
// la structure top qui contient les 50 premiers trajets classés par distance max - distance min
	Trajet* tab;
}Top2;
	
typedef struct arbre2{
// la structure pour l'AVL
	Trajet* elmt;
	int eq;
	struct arbre * fg;
	struct arbre * fd;
}Arbre2;

typedef Arbre2 * pArbre2;	

int min(int a,int b);

int max(int a,int b);

pArbre creationAVL(Ville *v);

int filsDroit(pArbre a);

int equilibre(pArbre a);

pArbre RG(pArbre a);

pArbre RD(pArbre a);

pArbre DRG(pArbre a);

pArbre DRD(pArbre a);

pArbre equilibrerAVL(pArbre a);

pArbre insertAVL(pArbre a,Ville* v,int* h);

Ville maxAVL(pArbre a);

pArbre supprmaxAVL(pArbre a);

Top podium(pArbre a);

Ville* tri(Ville* tab);

void sauvegarde(Top premier);

pArbre T(FILE* fichier,pArbre a,int* h);

pArbre2 creationAVL2(Trajet *t);

int filsDroit2(pArbre2 a);

int equilibre2(pArbre2 a);

pArbre2 RG2(pArbre2 a);

pArbre2 RD2(pArbre2 a);

pArbre2 DRG2(pArbre2 a);

pArbre2 DRD2(pArbre2 a);

pArbre2 equilibrerAVL2(pArbre2 a);

pArbre2 insertAVL2(pArbre2 a,Trajet* t,int* h);

Trajet maxAVL2(pArbre2 a);

pArbre2 supprmaxAVL2(pArbre2 a);

Top2 podium2(pArbre2 a);

Trajet* tri2(Trajet* tab);

void sauvegarde2(Top2 premier);

pArbre2 S(FILE* fichier,pArbre2 a,int* h);
