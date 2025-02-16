#!/bin/bash 
rm BenchGen petBoss
rm petBoss-source/petBoss.exe
rm BenchGen-source/BenchGen
cd petBoss-source
make
cd ../BenchGen-source 
make
cd ..
pwd
cp petBoss-source/petBoss.exe petBoss
cp BenchGen-source/BenchGen BenchGen

rm split-complex-gates
g++ scripts/split-complex-gates.cpp -o split-complex-gates

