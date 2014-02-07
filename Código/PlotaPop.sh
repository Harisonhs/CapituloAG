#!/bin/bash

echo "set terminal png" >> _tempPop.gnu
echo "set output \"Pop.png\"" >> _tempPop.gnu
echo "set xlabel \"longitude\"" >> _tempPop.gnu
echo "set ylabel \"latitude\"" >> _tempPop.gnu
echo "set style line 1 lt 1 lw 3" >> _tempPop.gnu
echo "set nokey" >> _tempPop.gnu
read linhaTitulo < Pop
echo "set title '$linhaTitulo'" >> _tempPop.gnu
echo "plot 'Pop' using 1:2 title \"x1\" with lines" >> _tempPop.gnu
/usr/bin/gnuplot _tempPop.gnu
rm _tempPop.gnu -f
gnome-terminal --command='eog Pop.png'
sleep 2
