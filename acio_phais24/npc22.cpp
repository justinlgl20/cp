#include "game.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <cassert>
#include <functional>
using namespace std;

static int id(int r, int c) {
    if (c < 0) return 66;
    if (c > 7) return 64;
    if (r < 0 or r > 7) return -1;
    return r*8+c;
}

static int adj[68];
static int path_end[68];
static double weight[68];

int no = 1;


Move nextMove(const std::vector<std::vector<Tile>> &board) {
    no++;

    //cerr << "HI\n";
    //for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) {cerr << i << " " << j << "\n";}
    try {
    vector<vector<Tile>> grid(8, vector<Tile>(8, {0, 0, 0}));
    for (int i = 0;i < 8; i++) {
        for (int j = 0; j < 8; j++) grid[i][j] = board[i][j];
    }
    // 0 is where we want to send it
    //cerr << "HI\n";
    // 64 is where we don't want to send it
    adj[66] = 66;
    adj[64] = 64;
    vector<pair<int, int>> selection;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            adj[id(i, j)] = id(grid[i][j].y+i, grid[i][j].x+j);
            selection.emplace_back(i, j);
        }
    }
    vector<Move> moves;
    vector<vector<int>> val(8, vector<int>(8, 0));

    function<int(int, int)> score = [&](int i, int j) {
        int s = ((8-j)*100)+grid[i][j].amount+rand()%(no);
        if (j == 7) return s;
        for (int q = -1; q <= 1; q++) {
            if (0 <= i+q and i+q < 8) s += val[i+q][j+1]/3;
        }
        return -s;
    };
    for (int i = 0; i < 8; i++) {
        for (int j = 7; j >= 0; j--) {
            val[i][j] = score(i, j);
        }
    }
    sort(selection.begin(), selection.end(), [&](pair<int, int> a, pair<int, int> b) {
            return val[a.first][a.second] < val[b.first][b.second];
    });
    for (auto _ : selection) {
        int i = _.first;
        int j = _.second;
        if (grid[i][j].x == 0) return {i, j, Left};
    }
    for (auto _ : selection) {
        int i = _.first;
        int j = _.second;
        if (no > 300 and rand()%5 == 0) continue;
        if (grid[i][j].y == 1 and i == 0) return {i, j, Down};
        if (grid[i][j].y == -1 and i == 7) return {i, j, Up};
    }
    for (auto _ : selection) {
        int i = _.first;
        int j = _.second;
            if (grid[i][j].x == 1) return {i, j, Left};
    }

    return {0, 0, None};
    } catch (int x) {
        return {0, 0, None};
    }
    
    //cerr << best.row << " " << best.column << " " << best.direction << "\n";
}

