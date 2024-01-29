#!bin/bash

gnuplot <<EOF
set terminal png size 1800,800
set term png font "Cambria,14"
green = "#008000"; green2 = "#00FF00"; green3 = "#004000"
set output 'figure5.png'
set datafile separator ';'
set ylabel 'DISTANCE (en km)' rotate by 270 center 	
set xlabel 'IDENTIFIANT DE TRAJET'
set x2label 'Option -s : Distances minimales, maximales et moyennes des étapes pour chaque trajet '
set xtic rotate by 40 center right
plot 'data_s.dat' using 1:3:5:xtic(2) with filledcurves fillstyle transparent solid 0.2 title "Distance max/min (en km)" linecolor rgb green, 'data_s.dat' using 1:3 with lines notitle linecolor rgb green2, 'data_s.dat' using 1:4 w l title "Distance moyenne (en km)" linecolor rgb green, 'data_s.dat' using 1:5 w l notitle linecolor rgb green3
EOF
mv figure5.png fichier
