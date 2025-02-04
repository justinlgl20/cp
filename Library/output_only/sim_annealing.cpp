int randint(int l, int r) {
    return rand()%(r-l+1)+l;
}

struct state {
    int oldscore;
    int score;
    //info
    void become_neighbour() {

    }
    void rollback() {

    }
};

double t = 100000;
double delta = 0.99999;

void upd_temp() {
    t = t*delta;
}

double p(int old, int ne) {
    if (ne > old) return 1.0;
    return exp((ne-old)/t);
}

void transition(state &current) {
    current.become_neighbour();
    if (p(current.oldscore, current.score)*1e9 >= randint(0, 1e9)) {
        // we go to current
        return;
    } else {
        current.rollback();
    }
}


