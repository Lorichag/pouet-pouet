#include "fonctions.h"
//strcmp
/*
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
*/
int min(int a,int b){
//fonction qui retourne la plus petite des 2 valeurs entrées en paramètres
	if(a<=b){
		return a;
	}
	return b;
}

int max(int a,int b){
//fonction qui retourne la plus grande des 2 valeurs entrées en paramètres
	if(a<=b){
		return b;
	}
	return a;
}

pArbre creationAVL(Ville *v){
//déclaration du Chainon
	pArbre a = malloc(sizeof(Arbre));
	if(a==NULL){
		exit(1);
	}
	// initialisation des paramètres
	a->elmt=v;
	a->fg=NULL;
	a->fd=NULL;
	a->eq=0;
	return a;
}

int filsDroit(pArbre a){
// On verifie si a a un fils droit
	if(a==NULL){
		return -1;
	}
	if(a->fd==NULL){
		return 0;
	}
	return 1; 
}

int equilibre(pArbre a){
//On met à jour l'équilibre du noeud 
	if(a==NULL){
		return 0;
	}
	if(a->eq<-1 || a->eq>1){
		return-1;
	}
	return 1+equilibre(a->fg)+equilibre(a->fd);
}

pArbre RG(pArbre a){
// On tourne à gauche en faisant attention a modifier les valeurs d'équivalence si nécéssaire
	if(a==NULL){
		return a;
	}
	int eqa,eqp;
	pArbre pivot=a->fd;
	a->fd=pivot->fg;
	pivot->fg=a;
	eqa=a->eq;
	eqp=pivot->eq;
	a->eq=eqa-max(eqp,0)-1;	
	pivot->eq=min(eqa-2,min(eqa+eqp-2,eqp-1));
	return pivot;
}

pArbre RD(pArbre a){
// On tourne à droite en faisant attention a modifier les valeurs d'équivalence si nécéssaire
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
	pivot->eq=max(eqa+2,max(eqa+eqp+2,eqp+1));
	return pivot;
}

pArbre DRG(pArbre a){
// On tourne à droite puis à gauche en faisant attention a modifier les valeurs d'équivalence si nécéssaire
	if(a==NULL){
		return a;
	}
	a->fd=RD(a->fd);
	return RG(a);
}

pArbre DRD(pArbre a){
// On tourne à gauche puis à droite en faisant attention a modifier les valeurs d'équivalence si nécéssaire
	if(a==NULL){
		return a;
	}
	a->fg=RG(a->fg);
	return RD(a);
}

pArbre equilibrerAVL(pArbre a){
//Fonctions qui fait les rotations nécéssaires au sein de l'AVL
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

pArbre insertAVL(pArbre a,Ville* v,int* h){
//Fonction qui ajoute une ville à l'AVL
	if(a==NULL){
	// si l'arbre est vide
		*h=1;
		a=creationAVL(v);
		return a;
	}
	else if(v->nbtrajet<a->elmt->nbtrajet){
	//si le nombre de trajet est inférieur à celui du noeud on va à gauche
		a->fg=insertAVL(a->fg,v,h);
		*h=-*h;
	}
	else if(v->nbtrajet>a->elmt->nbtrajet){
		//si le nombre de trajet est supérieur à celui du noeud on va à droite
		a->fd=insertAVL(a->fd,v,h);
	}
	else{
		//si elle est déjà dedans on ne fait rien
		*h=0;
		return a;
	}
	if(*h!=0){
		//on modifie les valeurs d'equilibre	
		a->eq=a->eq+*h;
		a=equilibrerAVL(a);	//on équilibre l'arbre si besoin
		if(a->eq==0){
			*h=0;
		}
		else{
			*h=1;
		}
	}
	return a;
}

Ville maxAVL(pArbre a){
//Fonction qui récupère le plus grand élément de l'AVL
	if(filsDroit(a)==1){
		return maxAVL(a->fd);
	}
	else{
		return *(a->elmt);
	}
}

pArbre supprmaxAVL(pArbre a){
//Fonction qui supprime le plus grand élément de l'AVL
	if(a==NULL){
	//Si l'arbre est nul
		return NULL;
	}
	if(a->fd!=NULL){
	// si le noueud a un fils droit on suprime son fils droit
		a->fd=supprmaxAVL(a->fd);
	}
	else{
		pArbre temp=a;
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

Top podium(pArbre a){
//Fonction qui va renvoyer un tableau contenant les 10 villes les plus traversées 
	Top visite;
	visite.tab=malloc(sizeof(Ville)*10);
	for(int x=0;x<10;x++){
		visite.tab[x]=maxAVL(a);	//on stocke la ville la plus traversées de l'AVL dans le tableau
		a=supprmaxAVL(a);		//on supprime ensuite cette valeur de l'AVL
	}
	return visite;
}

Ville* tri(Ville* tab){
//Fonction qui va trier le tableau des 10 villes les plus traversées pour les mettre dans l'ordre alphabétique
	int i,j,min;
	for(i=0;i<10;i++){
		min=i;	//on intialise l'indice min à l'indice de i
		for(j=i+1;j<10;j++){
			if(strcmp(tab[j].nom,tab[min].nom)<0){
			// si la ville à l'indice j est avant dans l'ordre alphabétique que celle à l'indice min 
				min=j;	// l'indice min devient l'indice j
			}
		}
		if(min!=i){	// si l'indice min n'est supérieur à celui de i
			Ville temp=tab[i];	// on échange de place les ville d'indice i et min
			tab[i]=tab[min];
			tab[min]=temp;	
		}
	}
	return tab;
}

void sauvegarde(Top premier){
//Fonction qui va ecrire les 10 villes les plus traversées dans un fichier csv
	FILE* fichier=fopen("T.csv","w");	//On créer le fichier T.csv
	if(fichier==NULL){
		exit(2);
	}
	for(int i=0;i<10;i++){
	// On écrit dans le fichier les 10 villes
		fprintf(fichier,"%s;%d;%d\n",premier.tab[i].nom,premier.tab[i].nbtrajet,premier.tab[i].nbdep);
	}
	fclose(fichier);
}

pArbre T(FILE* fichier,pArbre a,int* h){
// La fonction principale qui va réaliser le protocole -t 	(PS:le tout début c'est à dire comment parcourir chaque ligne du fichier csv et comment prendre séparemment les valeurs
	// séparées par des ";" à été réaliser par chatgpt mais tous le reste à été réaliser par ma personne
	char line[1000];
	Ville* nouv;
	while(fgets(line,sizeof(line),fichier) != NULL){	// on parcourt chaque ligne du fichier initial
		nouv=malloc(sizeof(Ville));
		char *token = strtok(line, ";");	// token prend les valeurs séparé par des ";"
		int numc=1;
		nouv->nbtrajet=0;
		nouv->nbdep=0;
		while (token != NULL){ // tant qu'on est pas arrivé au bout de la ligne
			if(numc==1){
				strcpy(nouv->nom,token); // on copie le nom de la ville dans le parametre nom de la structure ville	
			}		
			if(numc==2){
				nouv->nbtrajet=atoi(token);	 // on copie le nombre de trajet de la ville dans le parametre nbtrajet de la structure ville	
			}
			if(numc==3){
				nouv->nbdep=atoi(token);	 // on copie le nombre de fois que la ville est en départ d'étape dans le parametre nbdep de la structure ville
			}
			token = strtok(NULL, ";");
			numc++;
		}
		a=insertAVL(a,nouv,h);	// On insert la ville dans l'AVL
	}
	free(nouv);
	Top dix;	//On crée un élément de la structure top
	dix.tab=malloc(sizeof(Ville)*10); // On initialise le tableau de la structure Top   
	dix=podium(a); // on rentre les valeurs dans le tableau
	dix.tab=tri(dix.tab); // on tri le tableau
	sauvegarde(dix); // on ecrit le tableau dans un fichier csv
	return a;
}

/*
int main(int argc, char ** argv){
	FILE* fichier=NULL;
	fichier=fopen("tempst.csv","r");
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
*/
