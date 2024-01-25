#include "fonctions.h"

int main(int argc, char ** argv){
	FILE* fichier=NULL;
	int* h=malloc(sizeof(int));
	if(argv[1]="-t"){
		fichier=fopen("tempst.csv","r");
		if(fichier==NULL){
			exit(1);
		}
		pArbre a=NULL;
		a=T(fichier,a,h);
		fclose(fichier);
	}
	else if(argv[1]="-s"){
		fichier=fopen("tempss.csv","r");
		if(fichier==NULL){
			exit(2);
		}
		pArbre2 a=NULL;
		a=S(fichier,a,h);
		fclose(fichier);
	}
	free(h);
	return 0;
}
