#include <pstreams/pstream.h>
#include <string>
#include <iostream>
#include <fstream>

enum Direction {
    None = 0, Left = 1, Right = 2, Up = 3, Down = 4
};

struct Tile {
    int x = 0;//Negative: left, Positive: right
    int y = 0;//Negative: up, Positive: down
    unsigned int amount = 0;

    void apply(Direction d) {
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
    }

    void fix() {
        if (x < -1) x = -1;
        if (x > 1) x = 1;
        if (y < -1) y = -1;
        if (y > 1) y = 1;
    }
};

int main(int argc, char **argv) {
#ifdef FORWARD_STDERR
    auto out = std::ofstream("GAME_OUTPUT");
#else
    auto &out = std::cerr;
#endif
    std::string exec1(argv[1]);
    std::string exec2(argv[2]);
    redi::pstream first(exec1, redi::pstreams::pstdin | redi::pstreams::pstdout
                               #ifndef FORWARD_STDERR
                               | redi::pstreams::pstderr
#endif
    );
    redi::pstream second(exec2, redi::pstreams::pstdin | redi::pstreams::pstdout
                                #ifndef FORWARD_STDERR
                                | redi::pstreams::pstderr
#endif
    );
    int ROWS = 8, COLS = 8, ADD = 1, FLOW = 50, TURNS = 1000;
    out << ROWS << " " << COLS << " " << ADD << " " << FLOW << " " << TURNS << std::endl;
    first << ROWS << " " << COLS << " " << ADD << " " << FLOW << std::endl;
    second << ROWS << " " << COLS << " " << ADD << " " << FLOW << std::endl;
    std::vector<std::vector<Tile>> board = std::vector<std::vector<Tile>>(ROWS, std::vector<Tile>(COLS));
    size_t points_l = 0, points_r = 0;
    auto cleanup = [&]() {
        if (!first.rdbuf()->exited()) {
            first << "-1" << std::endl;
        }
        if (!second.rdbuf()->exited()) {
            second << "-1" << std::endl;
        }
    };
    auto valid = [&](int d, int r, int c) {
        return d >= 0 && d <= 4 && r >= 0 && r < ROWS && c >= 0 && c < COLS;
    };
    auto flip = [&](Direction d) {
        if (d == Left) return Right;
        if (d == Right) return Left;
        return d;
    };
    for (int turn = 0; turn < TURNS; ++turn) {
        bool good_a = true, good_b = true;
        int da, ra, ca;
        int db, rb, cb;
        first.out() >> da >> ra >> ca;
        second.out() >> db >> rb >> cb;
        if (first.rdbuf()->exited()) {
            good_a = false;
        }
        if (second.rdbuf()->exited()) {
            good_b = false;
        }
        if (good_a && good_b) {
            good_a = valid(da, ra, ca);
            good_b = valid(db, rb, cb);
            if (good_a && good_b) {
                cb = COLS - 1 - cb;
                db = flip((Direction) db);
                out << da << " " << ra << " " << ca << std::endl;
                out << db << " " << rb << " " << cb << std::endl;
                first << db << " " << rb << " " << cb << std::endl;
                second << ((int) flip((Direction) da)) << " " << ra << " " << COLS - 1 - ca << std::endl;
                board[ra][ca].apply((Direction) da);
                board[rb][cb].apply((Direction) db);
                board[ra][ca].fix();
                board[rb][cb].fix();
                for (int i = 0; i < ROWS; ++i) {
                    for (int j = 0; j < COLS; ++j) {
                        board[i][j].amount += ADD;
                    }
                }
                std::vector<std::vector<unsigned >> add = std::vector<std::vector<unsigned >>(ROWS,
                                                                                              std::vector<unsigned>(
                                                                                                      COLS, 0));
                for (int i = 0; i < ROWS; ++i) {
                    for (int j = 0; j < COLS; ++j) {
                        unsigned num = std::min(board[i][j].amount, (unsigned) FLOW);
                        board[i][j].amount -= num;
                        int ar = i;
                        int ac = j;
                        ac += board[i][j].x;
                        ar += board[i][j].y;
                        if (ar >= 0 && ar < ROWS && ac >= 0 && ac < COLS) add[ar][ac] += num;
                        if (ac < 0) points_l += num;
                        if (ac >= COLS) points_r += num;
                    }
                }
                for (int i = 0; i < ROWS; ++i) {
                    for (int j = 0; j < COLS; ++j) {
                        board[i][j].amount += add[i][j];
                    }
                }
            } else {
                if (good_a) {
                    std::cout << 1 << std::endl;
                    out << "DEAD 2" << std::endl;
                    return 2;
                } else if (good_b) {
                    std::cout << 2 << std::endl;
                    out << "DEAD 1" << std::endl;
                    return 1;
                } else {
                    std::cout << 0 << std::endl;
                    out << "DEAD ALL" << std::endl;
                    return 3;
                }
            }
        } else {
            if (good_a) {
                std::cout << 1 << std::endl;
                out << "DEAD 2" << std::endl;
                return -2;
            } else if (good_b) {
                std::cout << 2 << std::endl;
                out << "DEAD 1" << std::endl;
                return -1;
            } else {
                std::cout << 0 << std::endl;
                out << "DEAD ALL" << std::endl;
                return -3;
            }
        }
    }
    out << "END " << points_l << " " << points_r << std::endl;
    if (points_l == 0 && points_r == 0) {
        std::cout << -1 << std::endl;
    } else if (points_l > points_r) {
        std::cout << 1 << std::endl;
    } else if (points_r > points_l) {
        std::cout << 2 << std::endl;
    } else if (points_r == points_l) {
        std::cout << 0 << std::endl;
    }
    return 0;
}
