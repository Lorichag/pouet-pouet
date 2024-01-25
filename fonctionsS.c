#include "fonctions.h"
//strcmp
typedef struct trajet{
// la structure trajet qui contient 4 paramètres: l'id du trajet, la moyenne des distances du trajet, la distance maximale d'étape du trajet et la distance minimale d'étape du trajet
	int id;
	float moy;
	float max;
	float min;
}Trajet;

typedef struct top2{
// la structure top qui contient les 50 premiers trajets classés par distance max - distance min
	Trajet* tab;
}Top2;
	
typedef struct arbre2{
// la structure pour l'AVL
	Trajet* elmt;
	int eq;
	struct arbre2 * fg;
	struct arbre2 * fd;
}Arbre2;

typedef Arbre2 * pArbre2;	

int min2(int a,int b){
//fonction qui retourne la plus petite des 2 valeurs entrées en paramètres
	if(a<=b){
		return a;
	}
	return b;
}

int max2(int a,int b){
//fonction qui retourne la plus grande des 2 valeurs entrées en paramètres
	if(a<=b){
		return b;
	}
	return a;
}

pArbre2 creationAVL2(Trajet *t){
//déclaration du Chainon
	pArbre2 a = malloc(sizeof(Arbre2));
	if(a==NULL){
		exit(1);
	}
	// initialisation des paramètres de la structure d'AVL
	a->elmt=t;
	a->fg=NULL;
	a->fd=NULL;
	a->eq=0;
	return a;
}

int filsDroit2(pArbre2 a){
// On verifie si l'arbre a un fils droit
	if(a==NULL){
		return -1;
	}
	if(a->fd==NULL){
		return 0;
	}
	return 1; 
}

int equilibre2(pArbre2 a){
//On met à jour l'équilibre du noeud 
	if(a==NULL){
		return 0;
	}
	if(a->eq<-1 || a->eq>1){
		return-1;
	}
	return 1+equilibre2(a->fg)+equilibre2(a->fd);
}

pArbre2 RG2(pArbre2 a){
// On tourne à gauche en faisant attention a modifier les valeurs d'équivalence si nécéssaire
	if(a==NULL){
		return a;
	}
	int eqa,eqp;
	pArbre2 pivot=a->fd;
	a->fd=pivot->fg;
	pivot->fg=a;
	eqa=a->eq;
	eqp=pivot->eq;
	a->eq=eqa-max2(eqp,0)-1;	
	pivot->eq=min2(eqa-2,min2(eqa+eqp-2,eqp-1));
	return pivot;
}

pArbre2 RD2(pArbre2 a){
// On tourne à droite en faisant attention a modifier les valeurs d'équivalence si nécéssaire
	if(a==NULL){
		return a;
	}
	int eqa,eqp;
	pArbre2 pivot=a->fg;
	a->fg=pivot->fd;
	pivot->fd=a;
	eqa=a->eq;
	eqp=pivot->eq;
	a->eq=eqa-min2(eqp,0)+1;
	pivot->eq=max2(eqa+2,max2(eqa+eqp+2,eqp+1));
	return pivot;
}

pArbre2 DRG2(pArbre2 a){
// On tourne à droite puis à gauche en faisant attention a modifier les valeurs d'équivalence si nécéssaire
	if(a==NULL){
		return a;
	}
	a->fd=RD2(a->fd);
	return RG2(a);
}

pArbre2 DRD2(pArbre2 a){
// On tourne à gauche puis à droite en faisant attention a modifier les valeurs d'équivalence si nécéssaire
	if(a==NULL){
		return a;
	}
	a->fg=RG2(a->fg);
	return RD2(a);
}

pArbre2 equilibrerAVL2(pArbre2 a){
//Fonctions qui fait les rotations nécéssaires au sein de l'AVL
	if(a==NULL){
		return a;
	}
	if(a->eq>=2){
		if(a->fd->eq>=0){
			return RG2(a);
		}
		else{
			return DRG2(a);
		}
	}
	else if(a->eq<=-2){
		if(a->fg->eq<=0){
			return RD2(a);
		}
		else{
			return DRD2(a);
		}
	}
	return a;
}

pArbre2 insertAVL2(pArbre2 a,Trajet* t,int* h){
//Fonction qui ajoute un trajet à l'AVL
	if(a==NULL){
	// si l'arbre est vide
		*h=1;
		a=creationAVL2(t);
		return a;
	}
	else if(t->max-t->min < ((a->elmt->max)-(a->elmt->min))){
	//si la distance max - la distance min du trajet est inférieur à celui du noeud on va à gauche
		a->fg=insertAVL2(a->fg,t,h);
		*h=-*h;
	}
	else if(t->max-t->min > a->elmt->max-a->elmt->min){
		//si la distance max - la distance min du trajet est supérieur à celui du noeud on va à gauche
		a->fd=insertAVL2(a->fd,t,h);
	}
	else{
		//si elle est déjà dedans on ne fait rien
		*h=0;
		return a;
	}
	if(*h!=0){
		//on modifie les valeurs d'equilibre	
		a->eq=a->eq+*h;
		a=equilibrerAVL2(a);	//on équilibre l'arbre si besoin
		if(a->eq==0){
			*h=0;
		}
		else{
			*h=1;
		}
	}
	return a;
}

Trajet maxAVL2(pArbre2 a){
//Fonction qui récupère le plus grand élément de l'AVL
	if(filsDroit2(a)==1){
		return maxAVL2(a->fd);
	}
	else{
		return *(a->elmt);
	}
}

pArbre2 supprmaxAVL2(pArbre2 a){
//Fonction qui supprime le plus grand élément de l'AVL
	if(a==NULL){
	//Si l'arbre est nul
		return NULL;
	}
	if(a->fd!=NULL){
	// si le noueud a un fils droit on suprime son fils droit
		a->fd=supprmaxAVL2(a->fd);
	}
	else{
		pArbre2 temp=a;
		if(a->fg!=NULL){
		// si le noeud a un fils gauche a devient son fils gauche pour liberer l'ancien emplacement de a
			a=a->fg;
		}
		else{
			free(temp);
			return NULL;
		}
		free(temp);
	}
	return a;
}

Top2 podium2(pArbre2 a){
//Fonction qui va renvoyer un tableau contenant les 50 premiers trajets classés par ordre distance max - distance min
	Top2 visite;
	visite.tab=malloc(sizeof(Trajet)*50);
	for(int x=0;x<50;x++){
		visite.tab[x]=maxAVL2(a);	//on stocke le premier trajet classé par ordre distance max - distance min dans le tableau
		a=supprmaxAVL2(a);		//on supprime ensuite cette valeur de l'AVL
	}
	return visite;
}

Trajet* tri2(Trajet* tab){
//Fonction qui va trier le tableau des 50 premiers trajets classés par ordre distance max - distance min pour les mettre dans l'ordre croissant des id de trajet 
	int i,j,min;
	for(i=0;i<50;i++){
		min=i;	//on intialise l'indice min à l'indice de i
		for(j=i+1;j<50;j++){
			if(tab[j].id<tab[min].id){
			// si le trajet à l'indice j est avant dans l'ordre croissant que celui à l'indice min 
				min=j;	// l'indice min devient l'indice j
			}
		}
		if(min!=i){	// si l'indice min n'est supérieur à celui de i
			Trajet temp=tab[i];	// on échange de place les trajets d'indice i et min
			tab[i]=tab[min];
			tab[min]=temp;	
		}
	}
	return tab;
}

void sauvegarde2(Top2 premier){
//Fonction qui va ecrire les 50 premiers trajets classés par ordre distance max - distance dans un fichier csv
	FILE* fichier=fopen("S.csv","w");	//On créer le fichier S.csv
	if(fichier==NULL){
		exit(2);
	}
	for(int i=0;i<50;i++){
	// On écrit dans le fichier les 50 trajets
		fprintf(fichier,"%d;%f;%f;%f\n",premier.tab[i].id,premier.tab[i].moy,premier.tab[i].min,premier.tab[i].max);
	}
	fclose(fichier);
}

pArbre2 S(FILE* fichier,pArbre2 a,int* h){
// La fonction principale qui va réaliser le protocole -s 	(PS:le tout début c'est à dire comment parcourir chaque ligne du fichier csv et comment prendre séparemment les valeurs séparées par des ";" à été réaliser par chatgpt mais tous le reste à été réaliser par ma personne
	char line[1000];
	Trajet* nouv;
	while(fgets(line,sizeof(line),fichier) != NULL){	// on parcourt chaque ligne du fichier initial
		nouv=malloc(sizeof(Trajet));
		char *token = strtok(line, ";");	// token prend les valeurs séparé par des ";"
		int numc=1;
		nouv->moy=0;
		nouv->max=0;
		nouv->min=0;
		while (token != NULL){ // tant qu'on est pas arrivé au bout de la ligne
			if(numc==1){
				nouv->id=atoi(token); // on copie le nom de l'id du trajet dans le paramètre id de la structure trajet	
			}		
			if(numc==2){
				nouv->moy=atof(token);	 // on copie la moyenne des distances du trajet dans le parametre moy de la structure trajet	
			}
			if(numc==3){
				nouv->min=atof(token);	 // on copie la distance maximale du trajet dans le parametre moy de la structure trajet
			}
			if(numc==4){
				nouv->max=atof(token);	 // on copie la distance minimale du trajet dans le parametre moy de la structure trajet
			}
			token = strtok(NULL, ";");
			numc++;
		}
		a=insertAVL2(a,nouv,h);	// On insert le trajet dans l'AVL
	}
	free(nouv);
	Top2 dix;	//On crée un élément de la structure top2
	dix.tab=malloc(sizeof(Trajet)*10); // On initialise le tableau de la structure Top2   
	dix=podium2(a); // on rentre les valeurs dans le tableau
//	dix.tab=tri2(dix.tab); // on tri le tableau
	sauvegarde2(dix); // on ecrit le tableau dans un fichier csv
	return a;
}


int main(int argc, char ** argv){
	FILE* fichier=NULL;
	fichier=fopen("tempss.csv","r");
	if(fichier==NULL){
		exit(1);
	}
	pArbre2 a=NULL;
	int* h=malloc(sizeof(int));
	a=S(fichier,a,h);
	free(h);
	fclose(fichier);
	return 0;
}
