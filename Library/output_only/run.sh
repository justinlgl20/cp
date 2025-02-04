#!bin/bash

set -e

g++ -o $1 $1 -O2 -Wall

if [ -d 'output']; then
    echo 'Output directory exists'
else
    mkdir output
    echo 'Output directory created'
fi

if [-d 'input']; then
    echo 'Input directory exists'
else
    echo 'Failure, no input directory'
fi

./$1 > output/output$2.txt < input/input$2.txt
