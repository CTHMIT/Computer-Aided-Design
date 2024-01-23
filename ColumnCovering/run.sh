#!/bin/bash

g++ ./route.cpp -o ./route

files=('bench1.txt' 'bench2.txt' 'bench3.txt' 'bench4.txt' 'bench5.txt' 'bench6.txt')
for file in "${files[@]}"; do
    echo "Reading $file..."
    ./route "$file"
done
