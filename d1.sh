#!/bin/bash

gnuplot << EOF
set terminal png size 800,800
set term png font "Cambria,14"
green = "#008000"
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
plot 'resultd1.csv' using 2:xticlabels(1) axes x1y2 notitle linecolor rgb green
EOF
convert -rotate 90 graphvertical.png figured1.png 
mv figured1.png images
rm "graphvertical.png" 
