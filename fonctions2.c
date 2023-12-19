#include<stdio.h>
#include<stdlib.h>
#include <string.h>
//strcmp

typedef struct arbrec{
	char* elmt;
	int eq;
	struct arbrec * fg;
	struct arbrec * fd;
}Arbrec;

typedef struct ville{
	char nom[1000];
	int nbtrajet;
	int nbconducteurs;
	Arbrec* at;
	Arbrec* ac;
}Ville;

typedef struct top{
	Ville tab[10];
}Top;
	
typedef struct arbrev{
	Ville* elmt;
	int eq;
	struct arbrev * fg;
	struct arbrev * fd;
}Arbrev;

typedef Arbrec * pArbrec;
typedef Arbrev * pArbrev;		

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

pArbrec creationAVLc(char* nom){
//déclaration du Chainon
	pArbrec a = malloc(sizeof(Arbrec));
	if(a==NULL){
		exit(1);
	}
	a->elmt=nom;
	a->fg=NULL;
	a->fd=NULL;
	a->eq=0;
	return a;
}

int filsGauchec(pArbrec a){
	if(a==NULL){
		return -1;
	}
	if(a->fg==NULL){
		return 0;
	}
	return 1; 
}

int filsDroitc(pArbrec a){
	if(a==NULL){
		return -1;
	}
	if(a->fd==NULL){
		return 0;
	}
	return 1; 
}

int equilibrec(pArbrec a){
	if(a==NULL){
		return 0;
	}
	if(a->eq<-1 || a->eq>1){
		return-1;
	}
	return 1+equilibrec(a->fg)+equilibrec(a->fd);
}

pArbrec recherchec(pArbrec a,char* nom){
	if(a==NULL){
		return NULL;
	}
	else if(strcmp(a->elmt,nom)==0){
		return a;
	}
	else if(strcmp(nom,a->elmt)<0){
		return recherchec(a->fg,nom);
	}
	else{
		return recherchec(a->fd,nom);
	}
}

pArbrec RGc(pArbrec a){
	if(a==NULL){
		return a;
	}
	int eqa,eqp;
	pArbrec pivot=a->fd;
	a->fd=pivot->fg;
	pivot->fg=a;
	eqa=a->eq;
	eqp=pivot->eq;
	a->eq=eqa-min(eqp,0)+1;
	pivot->eq=max(eqa+2,max(eqa+eqp+2,eqp+1));
	return pivot;
}

pArbrec RDc(pArbrec a){
	if(a==NULL){
		return a;
	}
	int eqa,eqp;
	pArbrec pivot=a->fg;
	a->fg=pivot->fd;
	pivot->fd=a;
	eqa=a->eq;
	eqp=pivot->eq;
	a->eq=eqa-min(eqp,0)+1;
	pivot->eq=max(eqa-2,max(eqa-eqp-2,eqp-1));
	return pivot;
}

pArbrec DRGc(pArbrec a){
	if(a==NULL){
		return a;
	}
	a->fd=RDc(a->fd);
	return RGc(a);
}

pArbrec DRDc(pArbrec a){
	if(a==NULL){
		return a;
	}
	a->fg=RGc(a->fg);
	return RDc(a);
}

pArbrec equilibrerAVLc(pArbrec a){
	if(a==NULL){
		return a;
	}
	if(a->eq>=2){
		if(a->fd->eq>=0){
			return RGc(a);
		}
		else{
			return DRGc(a);
		}
	}
	else if(a->eq<=-2){
		if(a->fg->eq<=0){
			return RDc(a);
		}
		else{
			return DRDc(a);
		}
	}
	return a;
}

pArbrec insertAVLc(pArbrec a,char* mot,int* h){
	pArbrec new = malloc(sizeof(Arbrec));
	if(a==NULL){
		*h=1;
		a=creationAVLc(mot);
		return a;
	}
	else if(strcmp(mot,a->elmt)<0){
		a->fg=insertAVLc(a->fg,mot,h);
		*h=-*h;
	}
	else if(strcmp(mot,a->elmt)>0){
		a->fd=insertAVLc(a->fd,mot,h);
	}
	else{
		*h=0;
		return a;
	}
	if(*h!=0){
		a->eq=a->eq+*h;
		a=equilibrerAVLc(a);
		if(a->eq==0){
			*h=0;
		}
		else{
			*h=1;
		}
	}
	return a;
}

char* suppmaxc(pArbrec a){
	char* mot=a->elmt;
	if(!filsDroitc(a)){
		free(a);
		return mot;
	}
	pArbrec a2=a->fd;
	while(filsDroitc(a2)){
		a2=a2->fd;
		a=a->fd;
	}
	a->fd=a2->fg;
	mot=a2->elmt;
	free(a2);
	return mot;
}

pArbrec suppressionc(pArbrec a,char* nom){
	if(a==NULL){
		return a;
	}
	else if(strcmp(nom,a->elmt)<0){
		a->fg=suppressionc(a->fg,nom);
	}
	else if(strcmp(nom,a->elmt)>0){
		a->fd=suppressionc(a->fd,nom);
	}
	else if(a->elmt==nom){
		if(a->fg==NULL && a->fd==NULL){
			free(a);
			return NULL;
		}
		else if(filsGauchec(a)&&filsDroitc(a)){
			a->elmt=suppmaxc(a->fg);
		}
		else if(filsGauchec(a)){
			pArbrec tmp=a->fg;
			free(a);
			return tmp;
		}
		else{
			pArbrec tmp=a->fd;
			free(a);
			return tmp;
		}
	}
	return a;
}








pArbrev creationAVLv(Ville v){
//déclaration du Chainon
	pArbrev a = malloc(sizeof(Arbrev));
	if(a==NULL){
		exit(1);
	}
	a->elmt=&v;
	a->fg=NULL;
	a->fd=NULL;
	a->eq=0;
	return a;
}

int filsGauchev(pArbrev a){
	if(a==NULL){
		return -1;
	}
	if(a->fg==NULL){
		return 0;
	}
	return 1; 
}

int filsDroitv(pArbrev a){
	if(a==NULL){
		return -1;
	}
	if(a->fd==NULL){
		return 0;
	}
	return 1; 
}

int equilibrev(pArbrev a){
	if(a==NULL){
		return 0;
	}
	if(a->eq<-1 || a->eq>1){
		return-1;
	}
	return 1+equilibrev(a->fg)+equilibrev(a->fd);
}

pArbrev recherchev(pArbrev a,Ville v){
	if(a==NULL){
		return NULL;
	}
	else if(v.nom == a->elmt->nom){
		return a;
	}
	else if(strcmp(v.nom,a->elmt->nom)<0){
		return recherchev(a->fg,v);
	}
	else{
		return recherchev(a->fd,v);
	}
}

pArbrev RGv(pArbrev a){
	if(a==NULL){
		return a;
	}
	int eqa,eqp;
	pArbrev pivot=a->fd;
	a->fd=pivot->fg;
	pivot->fg=a;
	eqa=a->eq;
	eqp=pivot->eq;
	a->eq=eqa-min(eqp,0)+1;
	pivot->eq=max(eqa+2,max(eqa+eqp+2,eqp+1));
	return pivot;
}

pArbrev RDv(pArbrev a){
	if(a==NULL){
		return a;
	}
	int eqa,eqp;
	pArbrev pivot=a->fg;
	a->fg=pivot->fd;
	pivot->fd=a;
	eqa=a->eq;
	eqp=pivot->eq;
	a->eq=eqa-min(eqp,0)+1;
	pivot->eq=max(eqa-2,max(eqa-eqp-2,eqp-1));
	return pivot;
}

pArbrev DRGv(pArbrev a){
	if(a==NULL){
		return a;
	}
	a->fd=RDv(a->fd);
	return RGv(a);
}

pArbrev DRDv(pArbrev a){
	if(a==NULL){
		return a;
	}
	a->fg=RGv(a->fg);
	return RDv(a);
}

pArbrev equilibrerAVLv(pArbrev a){
	if(a==NULL){
		return a;
	}
	if(a->eq>=2){
		if(a->fd->eq>=0){
			return RGv(a);
		}
		else{
			return DRGv(a);
		}
	}
	else if(a->eq<=-2){
		if(a->fg->eq<=0){
			return RDv(a);
		}
		else{
			return DRDv(a);
		}
	}
	return a;
}

pArbrev insertAVLv(pArbrev a,Ville v,int* h){
	pArbrev new = malloc(sizeof(Arbrev));
	if(a==NULL){
		*h=1;
		a=creationAVLv(v);
		return a;
	}
	else if(strcmp(v.nom,a->elmt->nom)<0){
		a->fg=insertAVLv(a->fg,v,h);
		*h=-*h;
	}
	else if(strcmp(v.nom,a->elmt->nom)>0){
		a->fd=insertAVLv(a->fd,v,h);
	}
	else{
		*h=0;
		return a;
	}
	if(*h!=0){
		a->eq=a->eq+*h;
		a=equilibrerAVLv(a);
		if(a->eq==0){
			*h=0;
		}
		else{
			*h=1;
		}
	}
	return a;
}

Ville suppmaxv(pArbrev a,Ville* sup){
	Ville max;
	max=*(a->elmt);
	if(!filsDroitv(a)){
		free(a);
		return max;
	}
	pArbrev a2=a->fd;
	while(filsDroitv(a2)){
		a2=a2->fd;
		a=a->fd;
	}
	a->fd=a2->fg;
	max=*(a2->elmt);
	free(a2);
	return max;
}

pArbrev suppressionv(pArbrev a,Ville v,Ville* sup){
	if(a==NULL){
		return a;
	}
	else if(strcmp(v.nom,a->elmt->nom)<0){
		a->fg=suppressionv(a->fg,e);
	}
	else if(strcmp(v.nom,a->elmt->nom)>0){
		a->fd=suppressionv(a->fd,e);
	}
	else if(v.nom == a->elmt->nom){
		if(a->fg==NULL && a->fd==NULL){
			sup=&(a->elmt);
			free(a);
			return NULL;
		}
		else if(filsGauche(a)&&filsDroit(a)){
			a->elmt=suppmax(a->fg,sup);
		}
		else if(filsGauche(a)){
			pArbre tmp=a->fg;
			sup=&(a->elmt);
			free(a);
			return tmp;
		}
		else{
			pArbre tmp=a->fd;
			sup=&(a->elmt);
			free(a);
			return tmp;
		}
	}
	return a;
}

pArbrev T(FILE* fichier,pArbrev a,int* h){
	char line[1000];
	Ville nouv;
	Ville nouv2;
	nouv.nbtrajet=0;
	nouv.nbconducteurs=0;
	nouv.at=NULL;
	nouv.ac=NULL;
	Ville* sup=NULL;
	while(fgets(line,sizeof(line),fichier) != NULL){
		char *token = strtok(line, ";");
		int numc=1;
		while (token != NULL){
			if(numc==4){
				if(recherchev(a,nouv)!=NULL){
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
					a=insertAVL(a,nouv);
					}
				}
			}
				strcpy(nouv.nom,token);
			}
			if(numc==6){
				if(recherchec(nouv.ac,token)!=NULL){
					strcpy(nouv.condu[i],token);
					nouv.i++;
					nouv.nbconducteurs++;
				}
			}
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
	visite.tab=NULL
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
