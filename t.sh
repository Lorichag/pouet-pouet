#!/bin/bash

gnuplot << EOF
set terminal png size 1250,800
red = "#FF0000"; green = "#00FF00"; blue = "#0000FF"; skyblue = "#87CEEB";
set datafile separator ';'
set style data histogram
set style histogram cluster gap 1
set style fill solid
set output 'figure4.png'
set boxwidth 0.9
set xtics format ""
set grid ytics
set xlabel 'NOMS DES VILLES'
set ylabel 'NOMBRE DE TRAJETS'  rotate by 270 center 
set title "Option -t : Les 10 villes les plus travérsées"
plot "data_t.dat" using 2:xtic(1) title "total de trajets" linecolor rgb red,   \
     "data_t.dat" using 3 title "première ville" linecolor rgb blue
EOF
mv figure4.png fichier

#set boxwidth 0.8
#set xtics
#set ytics
#set ylabel 'ROUTES/DRIVERS NB'
#set xlabel 'CITY NAMES'
#set x2label 'Option -l : Nb routes =f(Driver) les 10 trajets les plus longs '
#set datafile separator ';'
#plot 'result.csv' using 2:xticlabels(1) axes x1y1 notitleset yrange

#set style data histogram
#set style histogram cluster gap 1
#set style fill solid
#set boxwidth 0.9
#set xtics format ""
#set grid ytics

#set terminal png size 800,800
#set boxwidth 0.9 relative
#set style data histograms
#set style histogram cluster
#set style fill solid 1.0 border lt -1
#set output 'figure4.png'
#plot for [COL=1:2:3] 'result.csv' using COL:xticlabels(1)

 #"test.csv" using 4 title "Jody" linecolor rgb green,    \
 #    "test.csv" using 5 title "Christina" linecolor rgb skyblue
