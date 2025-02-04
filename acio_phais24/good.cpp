#include "game.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <cassert>
#include <functional>
using namespace std;

int id(int i, int j) {
    if (j > 7) return 65;
    if (j < 0) return 66;
    if (i < 0 or j < 0 or i > 7 or j > 7) return 64;
    return i*8+j;
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
    vector<vector<int>> adj2(69, vector<int>());
    vector<pair<int, int>> selection;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            adj[id(i, j)] = id(grid[i][j].y+i, grid[i][j].x+j);
            for (int q : {-1, 0, 1, 0, 1, -1, 1, -1}) {
                for (int w : {0, 1, 0, -1, 1, 1, -1, -1}) {
                    adj2[id(i, j)].push_back(id(i+q, j+w));
                }
            }
            selection.emplace_back(i, j);
        }
    }
    vector<int> good(69, 1e9);
    vector<int> seen(68, 0);
    vector<int> order;
    function<void(int)> dfs = [&](int u) {
        seen[u] = true;
        if (!seen[adj[u]]) dfs(adj[u]);
        order.push_back(u);
    };
    for (int i = 0; i <= 66; i++) {
        if (!seen[i]) dfs(i);
    }
    vector<int> bad(68, 0);
    good[66] = 0;
    for (int i : order) {
        if (good[adj[i]]) good[i] = good[adj[i]] + 0;
        else {
            good[i] = 1e9;
            for (auto u : adj2[i]) {
                good[i] = min(good[i], good[u]+1); 
            }
        }
        
    }
    
    vector<Move> moves;
    vector<vector<int>> val(8, vector<int>(8, 0));

    function<int(int, int)> score = [&](int i, int j) {
        int s = ((200-good[id(i, j)])*130)+(int)grid[i][j].amount*1.3+rand()%(no);
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

