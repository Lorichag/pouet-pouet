#include<stdio.h>
#include<stdlib.h>
#include <string.h>
//strcmp
typedef struct ville{
	char nom[1000];
	int nbtrajet;
	int nbconducteurs;
}Ville;
	
typedef struct arbre{
	Ville* elmt;
	int eq;
	struct arbre * fg;
	struct arbre * fd;
}Arbre;

typedef Arbre * pArbre;	

int min(int a,int b){
	if(a<=b){
		return a;
	}
	return b;
}

int max(int a,int b){
	if(a<=b){
		return b;
	}
	return a;
}

pArbre creationAVL(Ville v){
//déclaration du Chainon
	pArbre a = malloc(sizeof(Arbre));
	if(a==NULL){
		exit(1);
	}
	a->elmt=&v;
	a->fg=NULL;
	a->fd=NULL;
	a->eq=0;
	return a;
}

int equilibre(pArbre a){
	if(a==NULL){
		return 0;
	}
	if(a->eq<-1 || a->eq>1){
		return-1;
	}
	return 1+equilibre(a->fg)+equilibre(a->fd);
}

pArbre recherche(pArbre a,Ville v){
	if(a==NULL){
		return NULL;
	}
	else if(strcmp(a->elmt->nom,v.nom)==0){
		return a;
	}
	else if(strcmp(v.nom,a->elmt->nom)<0){
		return recherche(a->fg,v);
	}
	else{
		return recherche(a->fd,v);
	}
}

pArbre RG(pArbre a){
	if(a==NULL){
		return a;
	}
	int eqa,eqp;
	pArbre pivot=a->fd;
	a->fd=pivot->fg;
	pivot->fg=a;
	eqa=a->eq;
	eqp=pivot->eq;
	a->eq=eqa-min(eqp,0)+1;
	pivot->eq=max(eqa+2,max(eqa+eqp+2,eqp+1));
	return pivot;
}

pArbre RD(pArbre a){
	if(a==NULL){
		return a;
	}
	int eqa,eqp;
	pArbre pivot=a->fg;
	a->fg=pivot->fd;
	pivot->fd=a;
	eqa=a->eq;
	eqp=pivot->eq;
	a->eq=eqa-min(eqp,0)+1;
	pivot->eq=max(eqa-2,max(eqa-eqp-2,eqp-1));
	return pivot;
}

pArbre DRG(pArbre a){
	if(a==NULL){
		return a;
	}
	a->fd=RD(a->fd);
	return RG(a);
}

pArbre DRD(pArbre a){
	if(a==NULL){
		return a;
	}
	a->fg=RG(a->fg);
	return RD(a);
}

pArbre equilibrerAVL(pArbre a){
	if(a==NULL){
		return a;
	}
	if(a->eq>=2){
		if(a->fd->eq>=0){
			return RG(a);
		}
		else{
			return DRG(a);
		}
	}
	else if(a->eq<=-2){
		if(a->fg->eq<=0){
			return RD(a);
		}
		else{
			return DRD(a);
		}
	}
	return a;
}

pArbre insertAVL(pArbre a,Ville v,int* h){
	pArbre new = malloc(sizeof(Arbre));
	if(a==NULL){
		*h=1;
		a=creationAVL(v);
		return a;
	}
	else if(strcmp(v.nom,a->elmt->nom)<0){
		a->fg=insertAVL(a->fg,v,h);
		*h=-*h;
	}
	else if(strcmp(v.nom,a->elmt->nom)>0){
		a->fd=insertAVL(a->fd,v,h);
	}
	else{
		*h=0;
		return a;
	}
	if(*h!=0){
		a->eq=a->eq+*h;
		a=equilibrerAVL(a);
		if(a->eq==0){
			*h=0;
		}
		else{
			*h=1;
		}
	}
	return a;
}

int checkExistence(char *chaine,char tableau[1000]) {
    int i = 0;
    while(tableau[i] != NULL){
        if (strcmp(chaine, tableau[i]) == 0) {
            return 1; // La chaîne existe dans le tableau
        }
        i++;
    }
    return 0; // La chaîne n'existe pas dans le tableau
}


void T(FILE* fichier,pArbre a,int* h){
	char line[1000];
	char condu[1000];
	int trajet[1000];
	Ville nouv;
	while(fgets(line,sizeof(line),fichier) != NULL){
		char *token = strtok(line, ";");
		int numc=1;
		int i=0;
		int j=0;
		nouv.nbtrajet=0;
		nouv.nbconducteurs=0;
		while (token != NULL){
			if(numc==1){
				strcpy(nouv.nom,token);
			}
			if(numc==2){
				if(!checkExistence(token,condu)){
					strcpy(condu[i],token);
					i++;
					nouv.nbconducteurs++;
				}
			}
			if(numc==3){
				if(!checkExistence(token,trajet)){
					strcpy(trajet[j],token);
					j++;
					nouv.nbtrajet++;
				}	
			}			
			token = strtok(NULL, ";");
			numc++;			
		}
		printf("%d %d \n",nouv.nbtrajet,nouv.nbconducteurs);
	}
}



int main(int argc, char ** argv){
	FILE* fichier=NULL;
	fichier=fopen("data2.csv","r");
	if(fichier==NULL){
		exit(1);
	}
	pArbre a=NULL;
	int* h=malloc(sizeof(int));
	T(fichier,a,h);
	free(h);
	fclose(fichier);
	return 0;
}
