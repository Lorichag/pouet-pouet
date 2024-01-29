#include "fonctions.h"

int main(int argc, char ** argv){
	FILE* fichier=NULL;
	int* h=malloc(sizeof(int));
	if (argc < 2) {
        printf("Utilisation : %s <option>\n", argv[0]);
        exit(1);
    	}
	if(strcmp(argv[1],"-t")==0){
		fichier=fopen("tempst.csv","r");
		if(fichier==NULL){
			exit(1);
		}
		pArbre a=NULL;
		a=T(fichier,a,h);
		free(h);
		fclose(fichier);
	}
	else if(strcmp(argv[1],"-s")==0){
		fichier=fopen("tempss.csv","r");
		if(fichier==NULL){
			exit(2);
		}
		pArbre2 a=NULL;
		a=S(fichier,a,h);
		free(h);
		fclose(fichier);
	}
	else{
        printf("Option invalide : %s\n", argv[1]);
        exit(1);
    	}
	return 0;
}
