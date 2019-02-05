#!/bin/bash
mv frame*.pgm sampleFrames
for i in `seq 0 435`;
do
    ./gen_dataset/genImage sampleFrames/frame$i.pgm headerOutput/frame$i.h
done