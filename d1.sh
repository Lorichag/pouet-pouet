#!/bin/bash

gnuplot << EOF
set terminal png size 800,800
set style data histogram
set style histogram cluster gap 1
set style fill solid border -1
set output 'graphvertical.png'
set boxwidth 0.8
set xtics rotate
set y2tics rotate 
set y2label 'NOMBRE DE TRAJETS EFFECTUES'
set xlabel 'NOMS DES CONDUCTEURS'
set ylabel 'Option -d1 : Conducteurs avec le plus de trajets '
unset ytics; set y2tics mirror
set datafile separator ';'
plot 'result.csv' using 2:xticlabels(1) axes x1y2 notitle linecolor 4
EOF
convert -rotate 90 graphvertical.png figure.png 
mv figure.png fichier
