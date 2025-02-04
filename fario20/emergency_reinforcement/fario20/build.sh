g++ -o Compiled reinforce.cpp
for var in 1 2 3 4 5 6 7 8
do
    echo $i
    ./Compiled < "test-$i.in" > "test-$i.out"
done
