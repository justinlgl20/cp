#pragma once

#include <vector>

enum Direction {
    None = 0, Left = 1, Right = 2, Up = 3, Down = 4
};

struct Tile {
    int x = 0;
    int y = 0;
    unsigned int amount = 0;

    void apply(Direction d);
};

struct Move {
    int row;
    int column;
    Direction direction;

    Move(int r, int c, Direction d) {
        row = r;
        column = c;
        direction = d;
    }
};

Move nextMove(const std::vector<std::vector<Tile>> &board);