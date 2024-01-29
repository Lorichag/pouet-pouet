#!/bin/bash

gnuplot << EOF
set terminal png size 800,800
set term png font "Cambria,13"
green = "#004000"
set style data histogram
set style histogram cluster gap 1
set style fill solid border -1
set output 'figurel.png'
set boxwidth 0.8
set xtics
set ytics
set ylabel 'DISTANCE (en km)' rotate by 270 center 	
set xlabel 'IDENTIFIANT DE TRAJET'
set x2label 'Option -l : Les 10 trajets les plus longs '
set datafile separator ';'
plot 'resultl.csv' using 2:xticlabels(1) axes x1y1 notitle linecolor rgb green
EOF
mv figurel.png images
