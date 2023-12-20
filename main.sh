#!/bin/bash

DATA=~/Info-Preing2/Projet/data.csv   #emplacement du fichier.csv
FICHIER=~/Info-Preing2/Projet/progc/exe  #emplacement du fichier.c
TEMP=~/Info-Preing2/Projet/temp
IMAGE=~/Info-Preing2/Projet/images
#Verifier si le fichier data.csv existe
if [ ! -f "$DATA" ]
then
	echo "Le fichier n'existe pas"
else
	echo "Le fichier data existe"
fi


#Verifie si L'executable du fichier C est présent ou non

if [ ! -x "$FICHIER" ]
then
	cd progc
	echo "l'executable n'existe pas"
	gcc -o exe camion.c 
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


#Verifie si le dossier temp existe si il existe déja il faut suprimer tout les fichier à l'interieur sion on le créer

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
fi


#Zone de test









#Apprendre awk
#https://www.malekal.com/awk-utilisation-et-exemples-fonctions-operateurs-et-boucles/
#https://www.malekal.com/comment-utiliser-la-commande-awk-avec-des-exemples/


if [ "$1" == "-h" ]
then
	echo "Les regles" #A faire
else
	for i in `seq 1 $#`
do
	case  ${!i} in
		'-d1')echo "Voici la liste des 10 conducteurs ayant fait le plus de trajet different" #Plus grand trajet garder les 10 premier conducteur en duree de trajet 
			start=$SECONDS	
			grep ";1;" data.csv | cut -d';' -f6 | sort -d | awk -F";" '{ line = $0 ; gsub(/\r/,"",line); if (line==pre_line) COUNT++; else {print pre_line ";" COUNT ;COUNT = 1}; pre_line = line;}' | sort -t';' -n -r -k2 | head -10 > result.csv
			cat result.csv
			duration=$(( SECONDS - start ))
			echo "Le programme à mis $duration seconde ";;
			
		
		
		'-d2')echo "Voici la liste des 10 conducteur ayant parcourus la plus grande distance" #Plus grande distance garder les 10 premier conducteur en distance
			start=$SECONDS	
			#awk -F';' '{print $5 ";" $6}' data.csv | sort -t";" -k2 | awk -F";" '{ line = $2; gsub(/\r/,"",line); if (line==preline) COUNT += $1 ; else {print preline ";" COUNT ;COUNT = $1 };preline = line;}' | sort -t';' -n -r -k2 | head -10 > result2.csv
			#cat result2.csv
			awk -F';' '{ camion[$6] += $5 ;} END { for (key in camion)print key ";" camion[key] ;}' data.csv | sort -t";" -k2nr | head -10 > result2.csv
			cat result2.csv
			duration=$(( SECONDS - start ))
			echo "Le programme à mis $duration seconde ";;
			
			
			
			
			
		'-l')echo "Voici la liste des 10 plus grand trajet" #Prendre la distance totale des 10 plus grands trajet
			start=$SECONDS
			#awk -F';' '{print $1 ";" $5}' data.csv | sort -t";" -n -k1 | awk -F";" '{ line = $1; gsub(/\r/,"",line); if (line==preline) COUNT += $2 ; else {print preline ";"  COUNT "km";COUNT = $2 };preline = line;}' | sort -t';' -n -r -k2 | head -10 > result3.csv
			#cat result3.csv
			awk -F';' '{ camion[$1] += $5 ;} END { for (key in camion)print key ";" camion[key]"km" ;}' data.csv | sort -t";" -k2nr | head -10 > result3.csv
			cat result3.csv 
			duration=$(( SECONDS - start ))
			echo "Le programme à mis $duration seconde ";;

		'-t')echo "Brownie";; #Affiche les 10 villes les plus traversé
		'-s')echo "Brownie";; #Bidule
		*) echo "erreur l'option  ${!i} n'existe pas" ;;
	esac
done
fi






