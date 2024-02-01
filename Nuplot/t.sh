#!/bin/bash

gnuplot << EOF
set terminal png size 1250,800
set term png font "Cambria,12"
green = "#008000"; green2 = "#00FF00";
set datafile separator ';'
set style data histogram
set style histogram cluster gap 1
set style fill solid
set output 'figuret.png'
set boxwidth 0.9
set xtics format ""
set grid ytics
set xlabel 'NOMS DES VILLES'
set ylabel 'NOMBRE DE TRAJETS'  rotate by 270 center 
set title "Option -t : Les 10 villes les plus travérsées"
plot "T.csv" using 2:xtic(1) title "total de trajets" linecolor rgb green,   \
     "T.csv" using 3 title "première ville" linecolor rgb green2
EOF
mv figuret.png images
