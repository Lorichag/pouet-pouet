#!/bin/bash

gnuplot << EOF
set terminal png size 800,800
set style data histogram
set style histogram cluster gap 1
set style fill solid border -1
set output 'graphvertical2.png'
set boxwidth 0.8
set xtics rotate
set y2tics rotate 
set y2label 'DISTANCE TOTALE PARCOURUE'
set xlabel 'NOMS DES CONDUCTEURS'
set ylabel 'Option -d1 : Conducteurs et la plus grande distance'
unset ytics; set y2tics mirror
set datafile separator ';'
plot 'result2.csv' using 2:xticlabels(1) axes x1y2 notitle
EOF
convert -rotate 90 graphvertical2.png figure2.png 
