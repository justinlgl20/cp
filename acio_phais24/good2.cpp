#include "game.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <cassert>
#include <functional>
#include <bits/stdc++.h>

using namespace std;


static int adj[68];
static int path_end[68];
int good[70];
static double weight[68]; // 64 is gone
//65 is theirs
//66 is ours

int no = 1;

int id(int i, int j) {
    if (j > 7) return 65;
    if (j < 0) return 66;
    if (i < 0 or j < 0 or i > 7 or j > 7) return 64;
    return i*8+j;
}

#define f first
#define s second

pair<int, int> last = {0, 0};


Move nextMove(const std::vector<std::vector<Tile>> &board) {
    srand(time(NULL));
    no++;
    try {
        vector<Move> moves;
        for (int i = 0; i < 69; i++) good[i] = false;
        good[66] = true;
        vector<int> val(69, 0);
        vector<vector<int>> radj(69, vector<int>());
        vector<vector<pair<int, pair<int, int>>>> adj2(69, vector<pair<int, pair<int, int>>>());
        vector<Tile> idk(69);
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                idk[id(i, j)] = board[i][j];
                val[id(i, j)] = board[i][j].amount;
                adj[id(i, j)] = id(i+board[i][j].y, j+board[i][j].x);
                radj[adj[id(i, j)]].push_back(id(i, j));
                for (int w : {1, 0, -1, 0, 1, -1, 1, -1}) {
                    for (int q : {0, -1, 0, 1, 1, -1, -1, 1}) {
                        adj2[id(i, j)].push_back(make_pair(id(i+w, j+q), make_pair(w, q)));
                    }
                }
                if (board[i][j].x != -1) {moves.push_back({i, j, Left});}
                if (board[i][j].x != 1) {moves.push_back({i, j, Right});}
                if (board[i][j].y != -1) {moves.push_back({i, j, Up});}
                if (board[i][j].y != 1) {moves.push_back({i, j, Down});}
            }
        }
        vector<int> seen(68, 0);
        vector<int> order;
        function<void(int)> dfs = [&](int u) {
            seen[u] = true;
            if (!seen[adj[u]]) dfs(adj[u]);
            order.push_back(u);
        };
        vector<int> vbad(69, 0);
        for (int i = 0; i <= 66; i++) {
            if (!seen[i]) dfs(i);
        }
        vector<int> bad(69, 1e9);
        vector<int> dist(69, 1e9);
        dist[66] = 0;
        bad[65] = 0;
        for (int i : order) {
            if (good[adj[i]]) good[i] = 1;
            bad[i] = min(bad[i], bad[adj[i]]+1);
            vbad[i] = vbad[adj[i]]+val[i];
            if (good[adj[i]]) {
                dist[i] = dist[adj[i]];
            } else {
                for (auto u : adj2[i]) {
                    if (u.f != 64)
                        dist[i] = min(dist[i], dist[u.f]+abs(idk[i].x - u.s.s)+abs(idk[i].y+u.s.f));
                }
            }
        }

        for (int i = 0; i < 69; i++) cerr << i << " " << dist[i] << " " << good[i] << "\n";
        
        reverse(order.begin(), order.end());

        vector<pair<int, Move>> options;
        for (int i = 0; i <= 67; i++) good[i] = false;
        queue<int> q;
        q.push(66);
        while (q.size()) {
            int u = q.front();
            q.pop();
            good[u] = true;
            for (auto i : radj[u]) {
                good[i] = true;
                q.push(i);
            }
        }

        for (auto i : moves) {
            //if connects a bad component to a good component, then take largest size
            //if its in the endgame, take most points
            if (good[id(i.row, i.column)]) continue;
            int r = i.row+board[i.row][i.column].y+(i.direction == 4) - (i.direction == 3);
            int c = i.column+board[i.row][i.column].x+(i.direction == 2) - (i.direction == 1);
            if (good[id(r, c)] == 0) continue;
            int score = (8-i.column)*200+dist[id(i.row, i.column)]*300;
            score += max((int)board[i.row][i.column].amount/30+50, (int)board[i.row][i.column].amount);
            score += rand()%max(1, (int)no/3);
            options.push_back(make_pair(score, i));
            //cerr << i.row << " " << i.column << " " << i.direction << "\n";
        }
        if (options.size() == 0) {
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    if (!good[id(i, j)]) return {i, j, Left};
                }
            }
            return {0, 0, None};
        }
        cerr << options.size() << "\n";

        // try up and down more, because people don't see that as much
        sort(options.begin(), options.end(), [&](pair<int, Move> a, pair<int, Move> b) {return a.first > b.first;});
        //reverse(options.begin(), options.end());
        cerr << board[options[0].second.row][options[0].second.column].x << " " << board[options[0].second.row][options[0].second.column].y << " " << options[0].second.row << " " << options[0].second.column << " " << options[0].second.direction << "\n";
        if (options[0].second.row == last.f and options[0].second.row == last.s and options.size() >= 2) {
            last = {options[1].second.row, options[1].second.column};
            return options[1].second;
        }
        last = {options[0].second.row, options[0].second.column};
        return options[0].second;


    } catch (int x) {
        cerr << "Hi\n";
        return {0, 0, None};
    }
    
    //cerr << best.row << " " << best.column << " " << best.direction << "\n";
}
