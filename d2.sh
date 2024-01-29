#!/bin/bash

gnuplot << EOF
set terminal png size 800,800
set term png font "Cambria,14"
green = "#006400"
set style data histogram
set style histogram cluster gap 1
set style fill solid border -1
set output 'graphvertical2.png'
set boxwidth 0.8
set xtics rotate
set y2tics rotate 
set y2label 'DISTANCE TOTALE PARCOURUE'
set xlabel 'NOMS DES CONDUCTEURS'
set ylabel 'Option -d2 : Conducteurs et la plus grande distance'
unset ytics; set y2tics mirror
set datafile separator ';'
plot 'resultd2.csv' using 2:xticlabels(1) axes x1y2 notitle linecolor rgb green
EOF
convert -rotate 90 graphvertical2.png figured2.png 
mv figured2.png images
rm "graphvertical2.png" 
