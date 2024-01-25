#include "fonctions.h"

int main(int argc, char ** argv){
	FILE* fichier=NULL;
	int* h=malloc(sizeof(int));
	if(argv[1]="-t"){ // si on lance le traitement T
		fichier=fopen("tempst.csv","r"); // on ouvre le fichier data simplifier correspondant
		if(fichier==NULL){
			exit(1);
		}
		pArbre a=NULL;
		a=T(fichier,a,h); // on appelle le code gérant le traitement T
		fclose(fichier); 
	}
	else if(argv[1]="-s"){ // si on lance le traitement S
		fichier=fopen("tempss.csv","r"); // on ouvre le fichier data simplifier correspondant
		if(fichier==NULL){
			exit(2);
		}
		pArbre2 a=NULL;
		a=S(fichier,a,h); // on appelle le code gérant le traitement S
		fclose(fichier);
	}
	free(h);
	return 0;
}
