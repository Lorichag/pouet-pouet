#!/bin/bash

gnuplot << EOF
set terminal png size 1900,800
set style data histogram
set style histogram cluster gap 1
set style fill solid border -1
set output 'figure3.png'
set boxwidth 0.8
set xtics
set ytics
set ylabel 'DISTANCE (en km)'
set xlabel 'IDENTIFIANT DE TRAJET'
set x2label 'Option -l : Les 10 trajets les plus longs '
set datafile separator ';'
plot 'result3.csv' using 2:xticlabels(1) axes x1y1 notitle
EOF
