#!/bin/bash

awk -F";" 'NR>1{count[$1";"$4]+=1 ; if($2==1) {count[$1";"$3]+=1;deb[$1";"$3]=1}} END{for(line in count) print line ";" count[line]";"deb[line]}' data.csv > t.csv
awk -F";" '{count[$2]+=1;deb[$2]+=$4} END {for(line in count) print line ";" count[line]";"deb[line]}' t.csv > tempst.csv
