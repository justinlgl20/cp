set -e

g++ -o $1 $1.cpp -O2 -Wall

if [ -d 'output' ]; then
    echo 'Output directory exists'
else
    mkdir output
    echo 'Output directory created'
fi

if [ -d 'input' ]; then
    echo 'Input directory exists'
else
    echo 'Failure, no input directory'
fi

echo "Running Test Case $2"

./$1 > output/output_$2.txt < input/input_$2.txt
