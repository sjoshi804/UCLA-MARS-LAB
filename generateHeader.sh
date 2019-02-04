#!/bin/bash
for i in `seq 0 435`;
do
    ./gen_dataset/genImage sampleFrames/Frames.pgm/frame$i.pgm frame$i.h
done