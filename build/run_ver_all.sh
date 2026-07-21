#!/bin/bash

#Change <num> to adjust the number of beams
num=1000

for pos in {-70..70..10}
do
	echo -e "\nCurrent beam position : ${pos}"

	sed -e "s/POS/${pos}/g" -e "s/NUM/${num}/g" run_ver.mac > run_ver_${pos}.mac

	./babel run_ver_${pos}.mac

	rm run_ver_${pos}.mac

done

hadd -f output_ver.root output_ver_*.root

rm output_ver_*.root
