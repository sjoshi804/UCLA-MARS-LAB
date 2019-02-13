#!/bin/bash
for i in `seq 350 360`;
do
    cp frame$i.pgm vj_cpp/Face.pgm 
    ./vj_cpp/vj
    mv vj_cpp/Output.pgm outputFrames/frame$i.pgm  
done