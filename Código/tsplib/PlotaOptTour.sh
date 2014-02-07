#!/bin/bash

for file in $( ls ./*.tsp ); do
	echo $file
	file2=`echo $file | sed 's/\.[^.]*$//'`
	number=$(echo $file | tr -cd '[[:digit:]]')	
	echo $number
	./OptGraph.cppo $number $file $file2.opt.tour
	echo "set terminal png" >> _tempPop.gnu
	echo "set output \"$file-OptTour.png\""  >> _tempPop.gnu
	echo "set xlabel \"longitude\"" >> _tempPop.gnu
	echo "set ylabel \"latitude\"" >> _tempPop.gnu
	echo "set style line 1 lt 1 lw 3" >> _tempPop.gnu
	echo "set nokey" >> _tempPop.gnu
	echo "plot \"Pop\" using 1:2 title \"x1\" with lines" >> _tempPop.gnu
	/usr/bin/gnuplot _tempPop.gnu
	rm _tempPop.gnu -f
	eog $file-OptTour.png
done
