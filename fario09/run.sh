g++ -o Compiled frag.cpp
for var in "$@"
do
    ./Compiled < input_$var.txt > output_$var.txt
done
