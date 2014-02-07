#!/bin/bash

echo "set terminal png" >> _tempPop.gnu
echo "set output \"Evo.png\"" >> _tempPop.gnu
echo "set xlabel \"geracao\"" >> _tempPop.gnu
echo "set ylabel \"nota\"" >> _tempPop.gnu
#echo "set style line 1 lt 1 lw 3" >> _tempPop.gnu
#echo "set nokey" >> _tempPop.gnu
#read linhaTitulo < Evolution
#echo "set title '$linhaTitulo'" >> _tempPop.gnu
echo "plot 'Evolution' using 1:2 title \"melhor\" with lines, \
	'Evolution' using 1:3 title \"pior\" with lines, \
	'Evolution' using 1:4 title \"media\" with lines" >> _tempPop.gnu
/usr/bin/gnuplot _tempPop.gnu
rm _tempPop.gnu -f
gnome-terminal --command='eog Evo.png'
sleep 2
