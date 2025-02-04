#include <iostream>
#include "game.h"

void Tile::apply(Direction d) {
    switch (d) {
        case Left:
            x--;
            break;
        case Right:
            x++;
            break;
        case Up:
            y--;
            break;
        case Down:
            y++;
            break;
        default:
            break;
    }
    if (x < -1) x = -1;
    if (x > 1) x = 1;
    if (y < -1) y = -1;
    if (y > 1) y = 1;
}

int main() {
    int ROWS, COLS, ADD, FLOW;
    std::cin >> ROWS >> COLS >> ADD >> FLOW;
    std::vector<std::vector<Tile>> board = std::vector<std::vector<Tile>>(ROWS, std::vector<Tile>(COLS));
    while (true) {
        Move next = nextMove(board);
        std::cout << ((int) next.direction) << " " << next.row << " " << next.column << std::endl;
        board[next.row][next.column].apply(next.direction);
        int x;
        std::cin >> x;
        if (x == -1) return 0;
        int r, c;
        std::cin >> r >> c;
        board[r][c].apply((Direction) x);
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                board[i][j].amount += ADD;
            }
        }
        std::vector<std::vector<unsigned>> add = std::vector<std::vector<unsigned>>(ROWS,
                                                                                    std::vector<unsigned>(COLS, 0));
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                unsigned num = std::min(board[i][j].amount, (unsigned) FLOW);
                board[i][j].amount -= num;
                int ar = i;
                int ac = j;
                ar += board[i][j].y;
                ac += board[i][j].x;
                if (ar >= 0 && ar < ROWS && ac >= 0 && ac < COLS) add[ar][ac] += num;
            }
        }
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                board[i][j].amount += add[i][j];
            }
        }
    }
}