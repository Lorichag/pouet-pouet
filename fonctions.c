#include<stdio.h>
#include<stdlib.h>
#include <string.h>
//strcmp
typedef struct ville{
	char nom[1000];
	int nbtrajet;
	int nbconducteurs;
	char* condu[1000]={0};
	char* trajet[1000]={0};
	int i=0;
	int j=0;
}Ville;

typedef struct top{
	Ville tab[10]=NULL;
}Top;
	
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

int filsDroit(pArbre a){
	if(a==NULL){
		return -1;
	}
	if(a->fd==NULL){
		return 0;
	}
	return 1; 
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




int checkExistence(char *chaine,char* tableau[1000]) {
    int i = 0;
    while(tableau[i] != NULL){
        if (strcmp(chaine, tableau[i]) == 0) {
            return 1; // La chaîne existe dans le tableau
        }
        i++;
    }
    return 0; // La chaîne n'existe pas dans le tableau
}

pArbre T(FILE* fichier,pArbre a,int* h){
	char line[1000];
	Ville nouv;
	Ville nouv2;
	while(fgets(line,sizeof(line),fichier) != NULL){
		char *token = strtok(line, ";");
		int numc=1;
		nouv.nbtrajet=0;
		nouv.nbconducteurs=0;
		while (token != NULL){
			if(numc==4){
				strcpy(nouv.nom,token);	
			}
			/*if(numc==6){
				if(!checkExistence(token,nouv.condu)){
					strcpy(nouv.condu[i],token);
					nouv.i++;
					nouv.nbconducteurs++;
				}
			}*/
			if(numc==1){
				if(!checkExistence(token,nouv.trajet)){
					printf("%s\n",token);
					strcpy(nouv.trajet[j],token);
					nouv.j++;
					nouv.nbtrajet++;
				}	
			}		
			/*if(numc==2 && token=="1"){
				char *token2 = strtok(line, ";");
				int numc2=1;
				nouv.nbtrajet2=0;
				nouv.nbconducteurs2=0;
				while (token2 != NULL){
					if(numc2==4){
						strcpy(nouv2.nom,token2);	
					}
					if(numc2==6){
						if(!checkExistence(token2,nouv2.condu)){
							strcpy(nouv2.condu[i],token2);
							nouv2.i++;
							nouv2.nbconducteurs++;
						}
					}
					if(numc2==1){
						if(!checkExistence(token2,nouv2.trajet)){
							printf("%s\n",token2);
							strcpy(nouv2.trajet[j],token2);
							nouv2.j++;
							nouv2.nbtrajet++;
						}	
					}		
					token2 = strtok(NULL, ";");
					numc2++;		
				}			
			}*/
			token = strtok(NULL, ";");
			numc++;
		}
		printf("%d %d \n",nouv.nbtrajet,nouv.nbconducteurs);
		/*if(recherche(a,nouv)!=NULL){
			pArbre temp;
			temp=recherche(a,nouv);
			if(checkExistence(nouv.condu[0],temp->elmt->condu)==0){
				 temp->elmt->nbconducteurs++;
			}
			if(checkExistence(nouv.trajet[0],a->elmt->trajet)==0){
				 temp->elmt->nbtrajets++;
			}
		}
		else{
			insertAVL(a,nouv);
		}*/
	}
	return a;
}

Ville maxAVL(a){
	if(filsDroit(a)==1){
		return maxAVL(a->fd);
	}
	else{
		return a;
	}
}

pArbre supprmaxAVL(a){
	if(filsDroit(a)==1){
		return supprmaxAVL(a->fd);
	}
	else{
		if(a->fg==NULL){
			free(a);
			return NULL;
		}
		else{
			pArbre temp;
			temp=a;
			a=a->fg;
			free(temp);
			return a;
		}
	}
}

Top podium(a){
	Top visite;
	for(int x,x<10,x++){
		visite.tab[x]=maxAVL(a->elmt);
		a=supprmaxAVL(a);
	}
	return visite;
}

int main(int argc, char ** argv){
	FILE* fichier=NULL;
	fichier=fopen("data.csv","r");
	if(fichier==NULL){
		exit(1);
	}
	pArbre a=NULL;
	int* h=malloc(sizeof(int));
	a=T(fichier,a,h);
	free(h);
	fclose(fichier);
	return 0;
}
