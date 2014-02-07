#!/bin/bash

echo "set terminal png" >> _tempPop.gnu
echo "set output \"Notas.png\"" >> _tempPop.gnu
echo "set xlabel \"Individuo\"" >> _tempPop.gnu
echo "set ylabel \"Nota\"" >> _tempPop.gnu
echo "set style line 1 lt 1 lw 3" >> _tempPop.gnu
echo "set nokey" >> _tempPop.gnu
read linhaTitulo < Notas
echo "set title '$linhaTitulo'" >> _tempPop.gnu
echo "plot 'Notas' using 1:2 title \"x1\" with points" >> _tempPop.gnu
/usr/bin/gnuplot _tempPop.gnu
rm _tempPop.gnu -f
gnome-terminal --command='eog Notas.png'
sleep 2
