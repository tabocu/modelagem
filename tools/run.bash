#!/bin/bash

echo Cleaning resource folder
rm ../resources/*

echo Creating kernel;
../application/application.out -g ../resources/w9_h9_d10_kernel.pgm 9 9 10;

for i in `seq 1 20`;
do
    echo Creating ${i}00 X ${i}00 image;
    ../application/application.out -g ../resources/w${i}00_h${i}00_d100.pgm ${i}00 ${i}00 100;
done 

echo ""

for i in `seq 1 20`;
do
    echo ""
    echo Convoluting ${i}00 X ${i}00 image;
    ../application/application.out -c ../resources/w${i}00_h${i}00_d100.pgm ../resources/w9_h9_d10_kernel.pgm ../resources/w${i}00_h${i}00_d100_conv.pgm;
    echo ""
    echo \nKernel for ${i}00 X ${i}00;
    ../kernel/kernel.out -k ${i}00 ${i}00 9 9; 
done 
