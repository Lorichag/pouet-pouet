#!/bin/bash

DATA=~/Info-Preing2/Projet/data.csv   #emplacement du fichier.csv
FICHIER=~/Info-Preing2/Projet/progc/exe  #emplacement du fichier.c
TEMP=~/Info-Preing2/Projet/temp
IMAGE=~/Info-Preing2/Projet/images
#Verifier si le fichier data.csv existe
if [ ! -f "$DATA" ]
then
	echo "Le fichier n'existe pas"
		echo "Erreur l'executable n'existe toujours pas"
else
	echo "Le fichier data existe"
fi


#Verifie si L'executable du fichier C est présent ou non

if [ ! -x "$FICHIER" ]
then
	cd progc
	echo "L'executable n'existe pas"
	make 
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
else
	mv images/* demo/
fi


cp $0 data





#Zone de test




#awk -F';' '/32974;/ { print $0 ;}' data.csv | sort -t';' -k5n > caca.csv   #Affiche le trajet 105995

#Pour lolo



#Etape 1


#awk -F';' '/;1;/{ camion[$3] += 1 ;} END { for (key in camion)print key ";" camion[key] ;}' data.csv > lolo.csv

#awk -F';' '{print $4 ";" $1}' data.csv | awk -F";" '{ line = $0 ; gsub(/\r/,"",line); if (line==pre_line) COUNT+=1; else {print pre_line ";" COUNT ;COUNT = 1}; pre_line = line;}' > lolo2.csv

#awk -F';' '{ camion[$1] += 1 ;} END { for (key in camion)print key ";" camion[key] ;}' lolo2.csv > lolo3.csv

#awk -F ';' 'NR==FNR { a[$1]=$2; next } { print $0 ";" a[$1] ;}' lolo3.csv lolo.csv > resultat.csv 


#ETAPE 1 MATHIS 

#awk -F";" 'NR>1{count[$1";"$4]+=1 ; if($2==1) {count[$1";"$3]+=1;deb[$1";"$3]=1}} END{for(line in count) print line ";" count[line]";"deb[line]}' data.csv > t.csv
#awk -F";" '{count[$2]+=1;deb[$2]+=$4} END {for(line in count) print line ";" count[line]";"deb[line]}' t.csv > tempst.csv




# Etape 2

#LC_NUMERIC=C awk -F';' 'NR>1 {if ($5 > max_value[$1]) {max_value[$1] = $5;}}END { for (key in max_value) print key ";" max_value[key];}' data.csv > distmax.csv
#LC_NUMERIC=C awk -F';' 'NR>1 { if ($5 < min_value[$1] || min_value[$1]=="") min_value[$1] = $5;}END { for (key in min_value) print key ";" min_value[key];}' data.csv > distmin.csv


#LC_NUMERIC=C awk -F';' '{ camion_sum[$1] += $5;camion_count[$1]+=1;if ($5 > max_value[$1]) max_value[$1]=$5; if ($5 < min_value[$1] || min_value[$1]=="") min_value[$1]=$5;}END {for (line in camion_sum) {print line ";" camion_sum[line]/camion_count[line] ";" min_value[line] ";" max_value[line]}}' data.csv > tempss.csv 



#awk -F ';' 'NR==FNR { a[$1]=$2; next } { print $0 ";" a[$1] ;}' distmin.csv distmoy1.csv > LOLO.csv 
#awk -F ';' 'NR==FNR { a[$1]=$2; next } { print $0 ";" a[$1] ;}' distmax.csv LOLO.csv > AH.csv 
  
  
  
  
           
#awk -F';' 'NR>1{ camion[$1] += $5 ;} END { for (key in camion)print key ";" camion[key]"km" ;}' data.csv | sort -t";" -k2n > distmin.csv


#Pour chaque ville compter le nombre de trajet different et le nombre de fois ou ils sont à l'étape 1



#Apprendre awk
#https://www.malekal.com/awk-utilisation-et-exemples-fonctions-operateurs-et-boucles/
#https://www.malekal.com/comment-utiliser-la-commande-awk-avec-des-exemples/


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
	.[BONUS] La commande -ch permet de chercher un conducteur et d'afficher toute ça fiche trajet "
	exit 0
fi	
done

for i in `seq 1 $#`
do
	case  ${!i} in
		'-d1')echo "Voici la liste des 10 conducteurs ayant fait le plus de trajets different" #Plus grand trajet garder les 10 premier conducteur en duree de trajet 
			start=$SECONDS	
			grep ";1;" data.csv | cut -d';' -f6 | sort -d | LC_NUMERIC=C awk -F";" '{ line = $0 ; gsub(/\r/,"",line); if (line==pre_line) COUNT++; else {print pre_line ";" COUNT ;COUNT = 1}; pre_line = line;}' | sort -t';' -n -r -k2 | head -10 > resultd1.csv
			cat resultd1.csv				
			bash d1.sh
			mv resultd1.csv temp
			duration=$(( SECONDS - start ))
			echo "Le programme à mis $duration secondes ";;
			
		
		
		'-d2')echo "Voici la liste des 10 conducteurs ayant parcourus la plus grande distance" #Plus grande distance garder les 10 premier conducteur en distance
			start=$SECONDS	
			#awk -F';' '{print $5 ";" $6}' data.csv | sort -t";" -k2 | awk -F";" '{ line = $2; gsub(/\r/,"",line); if (line==preline) COUNT += $1 ; else {print preline ";" COUNT ;COUNT = $1 };preline = line;}' | sort -t';' -n -r -k2 | head -10 > result2.csv
			#cat result2.csv
			LC_NUMERIC=C awk -F';' '{ camion[$6] += $5 ;} END { for (key in camion)print key ";" camion[key] ;}' data.csv | sort -t";" -k2nr | head -10 > resultd2.csv
			cat resultd2.csv
			bash d2.sh
			mv resultd2.csv temp
			duration=$(( SECONDS - start ))
			echo "Le programme à mis $duration secondes ";;
			
			
			
			
			
		'-l')echo "Voici la liste des 10 plus grands trajets" #Prendre la distance totale des 10 plus grands trajet
			start=$SECONDS
			#awk -F';' '{print $1 ";" $5}' data.csv | sort -t";" -n -k1 | awk -F";" '{ line = $1; gsub(/\r/,"",line); if (line==preline) COUNT += $2 ; else {print preline ";"  COUNT "km";COUNT = $2 };preline = line;}' | sort -t';' -n -r -k2 | head -10 > result3.csv
			#cat result3.csv
			LC_NUMERIC=C awk -F';' '{ camion[$1] += $5 ;} END { for (key in camion)print key ";" camion[key]"km" ;}' data.csv | sort -t";" -k2nr | head -10 > resultl.csv
			cat resultl.csv 
			bash l.sh
			mv resultl.csv temp
			duration=$(( SECONDS - start ))
			echo "Le programme à mis $duration secondes ";;
			
		'-ch')echo "Voici la liste des trajets de $prenom"
			#Objectif créer une nouvelle commande qui permet de rechercher le Prenom et le nom d'une personne dans le fichier

			echo "Quel conducteur voulez vous rechercher (Prenom Nom exemple: John Costa) ? "
			read prenom
			start=$SECONDS	
			awk -F';' -v prenom="$prenom" 'tolower($6) ~ tolower(prenom) { print $0 ;}' data.csv | sort -t';' -n -k1 -k2 > temp/"$prenom.csv"
			if [ ! -s temp/"$prenom.csv" ]; then
  			echo "Aucune personne avec le prénom $prenom n'a été trouvée."
    			`rm temp/"$prenom.csv"`
			fi 
			duration=$(( SECONDS - start ))
			echo "Le programme à mis $duration secondes ";;
			
			

		'-t')echo "Affiche les 10 villes les plus traversées"
			start=$SECONDS	
			awk -F";" 'NR>1{count[$1";"$4]+=1 ; if($2==1) {count[$1";"$3]+=1;deb[$1";"$3]=1}} END{for(line in count) print line ";" count[line]";"deb[line]}' data.csv > t.csv
			awk -F";" '{count[$2]+=1;deb[$2]+=$4} END {for(line in count) print line ";" count[line]";"deb[line]}' t.csv > tempst.csv
			#make cleanobj
			./progc/mon_programme -t
			bash t.sh
			mv tempst.csv temp
			mv t.csv temp
			mv T.csv temp
			duration=$(( SECONDS - start ))
			echo "Le programme à mis $duration secondes ";;
		

		
		
		
		
		'-s')echo "Affiche la moyenne le max et le min pour les 50 plus grandes distances(max-min)"
		start=$SECONDS	
		LC_NUMERIC=C awk -F';' '{ camion_sum[$1] += $5;camion_count[$1]+=1;if ($5 > max_value[$1]) max_value[$1]=$5; if ($5 < min_value[$1] || min_value[$1]=="") min_value[$1]=$5;}END {for (line in camion_sum) {print line ";" camion_sum[line]/camion_count[line] ";" min_value[line] ";" max_value[line]}}' data.csv > tempss.csv 
			#make 
			#make cleanobj
			./progc/mon_programme -s
			bash s.sh
			mv tempss.csv temp
			mv S.csv temp
			duration=$(( SECONDS - start ))
			echo "Le programme à mis $duration secondes ";;
		
		
		*) echo "Erreur l'option  ${!i} n'existe pas" ;;
	esac
done





