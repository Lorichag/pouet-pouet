#!/bin/bash

DATA=data
DATA1=data.csv   #emplacement du fichier.csv
DATA2=data/data.csv    #emplacement du fichier.csv
FICHIER=progc/exe  #emplacement du fichier.c
TEMP=temp	#emplacement du dossier
IMAGE=images  #emplacement du dossier

if [ ! -d "$DATA" ]
then
	mkdir data
fi

if [ -f "$DATA1" ]
then
	mv data.csv data
fi

#Verifier si le fichier data.csv existe
if [ ! -f "$DATA2" ]
then
	echo "Le fichier data.csv n'existe pas dans le fichier data"
	exit 1
else
	echo "Le fichier data existe"
fi


#Verifie si L'executable du fichier C est présent ou non

if [ ! -x "$FICHIER" ]
then
	cd progc
	echo "L'executable n'existe pas"
	make cleanobj
	cd ..
	if [ ! -x "$FICHIER" ]
	then
		echo "Erreur l'executable n'existe toujours pas"
	else
		echo "L'executable est maintenant opérationnel"
	fi
else
	echo "L'éxecutable existe"
fi


#Verifie si le dossier temp existe si il existe déja il faut suprimer tout les fichiers à l'interieur sion on le créer

if [ ! -d "$TEMP" ]
then
	mkdir temp
else
	cd temp
	rm -f *
	cd ..
fi
#Verifie si le dossier images existe sinon le créer
if [ ! -d "$IMAGE" ]
then
	mkdir images
else
	mv images/* demo/
fi


for i in `seq 1 $#`
do
 if [ "${!i}" == "-h" ]
	then
		echo "Voici les options pouvant être utilisées pour analyser notre fichier:
	.La commande -d1 permet d'afficher les 10 conducteurs ayant fait le plus de trajets.
	.La commande -d2 permet d'afficher les 10 conducteurs ayant parcourus la plus grande distance durant leur trajet.
	.La commande -l permet d'afficher les 10 plus longs trajets en distance.
	.La commande -t permet d'afficher les 10 villes les plus traversées.
	.La commande -s permet d'afficher une moyenne de distance entre chaque étape d'un trajet. 
	.[BONUS] La commande -ch permet de chercher un conducteur et d'afficher toute ça fiche trajet
	.[BONUS] La commande -id permet de chercher un id et d'afficher toutes ces étapes "
	
	exit 0
fi	
done

for i in `seq 1 $#`
do
	case  ${!i} in
		'-d1')echo "Voici la liste des 10 conducteurs ayant fait le plus de trajets different" #Plus grand trajet garder les 10 premier conducteur en duree de trajet 
			debut=$SECONDS	
			grep ";1;" data/data.csv | cut -d';' -f6 | sort -d | LC_NUMERIC=C awk -F";" '{ ligne = $0 ; gsub(/\r/,"",ligne); if (ligne==pre_ligne) COUNT++; else {print pre_ligne ";" COUNT ;COUNT = 1}; pre_ligne = ligne;}' | sort -t';' -n -r -k2 | head -10 > resultd1.csv				
			bash Nuplot/d1.sh
			mv resultd1.csv temp
			duration=$(( SECONDS - debut ))
			echo "Le programme à mis $duration secondes ";;
			
		
		
		'-d2')echo "Voici la liste des 10 conducteurs ayant parcourus la plus grande distance" #Plus grande distance garder les 10 premier conducteur en distance
			debut=$SECONDS	
			LC_NUMERIC=C awk -F';' '{ camion[$6] += $5 ;} END { for (ligne in camion)print key ";" camion[ligne] ;}' data/data.csv | sort -t";" -k2nr | head -10 > resultd2.csv
			bash Nuplot/d2.sh
			mv resultd2.csv temp
			duration=$(( SECONDS - debut ))
			echo "Le programme à mis $duration secondes ";;
			
			
			
			
			
		'-l')echo "Voici la liste des 10 plus grands trajets" #Prendre la distance totale des 10 plus grands trajet
			debut=$SECONDS
			LC_NUMERIC=C awk -F';' '{ camion[$1] += $5 ;} END { for (ligne in camion)print key ";" camion[ligne]"km" ;}' data/data.csv | sort -t";" -k2nr | head -10 > resultl.csv
			bash Nuplot/l.sh
			mv resultl.csv temp
			duration=$(( SECONDS - debut ))
			echo "Le programme à mis $duration secondes ";;
			
		'-ch')echo "Voici la liste des trajets du prenom choisit"
			#Objectif créer une nouvelle commande qui permet de rechercher le Prenom et le nom d'une personne dans le fichier

			echo "Quel conducteur voulez vous rechercher (Prenom Nom exemple: John Costa) ? "
			read prenom
			debut=$SECONDS	
			awk -F';' -v prenom="$prenom" 'tolower($6) ~ tolower(prenom) { print $0 ;}' data/data.csv | sort -t';' -n -k1 -k2 > temp/"$prenom.csv"
			if [ ! -s temp/"$prenom.csv" ]; then
  			echo "Aucune personne avec le prénom $prenom n'a été trouvée"
    			`rm temp/"$prenom.csv"`
			fi 
			duration=$(( SECONDS - debut ))
			echo "Le programme à mis $duration secondes ";;
			
			
		'-id')echo "Voici la liste des étape de l'id choisit"
			#Objectif créer une nouvelle commande qui permet de rechercher un id dans le fichier data et d'afficher les information sur les trajet de cet id

			echo "Quel id voulez vous rechercher ? "
			read id
			debut=$SECONDS	
			awk -F';' -v id="$id" '{if ($1 == id) print $0;}' data/data.csv | sort -t';' -n -k2 > temp/"$id.csv"
			if [ ! -s temp/"$id.csv" ]; then
  			echo "Aucune personne avec l'id $id n'a été trouvée"
    			`rm temp/"$id.csv"`
			fi 
			duration=$(( SECONDS - debut ))
			echo "Le programme à mis $duration secondes ";;	
			

		'-t')echo "Affiche les 10 villes les plus traversées"
			debut=$SECONDS	
			awk -F";" 'NR>1{calcul[$1";"$4]+=1 ; if($2==1) {calcul[$1";"$3]+=1;temp[$1";"$3]=1}} END{for(ligne in calcul) print ligne ";" calcul[ligne]";"temp[ligne]}' data/data.csv > t.csv
			awk -F";" '{calcul[$2]+=1;temp[$2]+=$4} END {for(ligne in calcul) print ligne ";" calcul[ligne]";"temp[ligne]}' t.csv > tempst.csv
			./progc/mon_programme -t
			bash Nuplot/t.sh
			mv tempst.csv temp
			mv t.csv temp
			mv T.csv temp
			duration=$(( SECONDS - debut ))
			echo "Le programme à mis $duration secondes ";;
		

		'-s')echo "Affiche la moyenne,le max,le min pour les 50 plus grandes distances(max-min)"
		debut=$SECONDS	
		LC_NUMERIC=C awk -F';' '{ camion[$1] += $5;camion_calcul[$1]+=1;if ($5 > max[$1]) max[$1]=$5; if ($5 < min[$1] || min[$1]=="") min[$1]=$5;}END {for (ligne in camion) {print ligne ";" camion[ligne]/camion_calcul[ligne] ";" min[ligne] ";" max[ligne]}}' data/data.csv > tempss.csv 
			./progc/mon_programme -s
			bash Nuplot/s.sh
			mv tempss.csv temp
			mv S.csv temp
			duration=$(( SECONDS - debut ))
			echo "Le programme à mis $duration secondes ";;
		
		
		*) debut=$SECONDS
			echo "Erreur l'option  ${!i} n'existe pas" 
			duration=$(( SECONDS - debut ))
			echo "Le programme à mis $duration secondes ";;
	esac
done



