g++ -std=c++20 -O2 -Wall -o exe1 good.cpp grader.cpp -DDEBUG -fsanitize=address -g
g++ -std=c++20 -O2 -Wall -o exe2 good2.cpp grader.cpp -DDEBUG -fsanitize=address -g
g++ -o runner runner.cpp -std=c++20 -DFORWARD_STDERR -fsanitize=address -g
time ./runner ./exe1 ./exe2 2>game_output
