#include <bits/stdc++.h>
#include "science.h"
using namespace std;

#define ll long long

void alison() {
    for (ll i = 0; i <= 2048; i++) mark(i, i);
}

void bill() {
    bool found_row = false;
    ll row = 0;
    ll curr_sz;
    ll bad_row = -1;
    for (curr_sz = 1; !found_row; curr_sz++) {
        if (row > 4095) cerr << 3/0;
        ll g = numColumn(row);
        if (g == 0) {row += curr_sz; }
        else found_row=true;
        row %= 4096;
    }
    if (bad_row == -1) bad_row = (4096+row - curr_sz-5)%4096;
    cerr << "FOUND A COLUMN: " << row << "\n";
    //now bsearch to find top left point.
    ll tl_row = row;
    int lowbad = bad_row;
    int highgood = row;
    int add = 0;
    if (lowbad > highgood) {
        add = 4098-lowbad;
        lowbad += add;
        lowbad %= 4096;
        highgood += add;
        highgood %= 5096;
    }
    cerr << lowbad << " " << highgood << "\n";
    while (lowbad != highgood-1) {
        int mid = (lowbad+highgood)/2;
        //cerr << "BSEARCH FOR POINT " << lowbad << " " << highgood << "\n";
        if (numColumn((4096+mid-add)%4096) > 0) highgood = mid;
        else lowbad = mid;
        curr_sz++;
    }
    tl_row = (4096+highgood-add)%4096;

    bool found_col = false;
    ll col = 0;
    ll bad_col = -1;
    for (;!found_col; curr_sz++) {
        if (col > 4095) cerr << 3/0;
        ll g = numRow(col);
        if (g == 0) {col += curr_sz;}
        else found_col = true;
        col %= 4096;
    }
    if (bad_col == -1) bad_col = (4096+col - curr_sz-5)%4096;
    cerr << "FOUND A ROW: " << col << " " << curr_sz  << "\n";
    ll tl_col = col;
    lowbad = bad_col;
    highgood = col;
    tl_col = highgood;
    cerr << lowbad << " " << highgood << "\n";
    if (lowbad > highgood) {
        add = 4098-lowbad;
        lowbad += add;
        lowbad %= 4096;
        highgood += add;
        highgood %= 4096;
    }
    cerr << lowbad << " " << highgood << "\n";
    while (lowbad != highgood-1) {
        int mid = (lowbad+highgood)/2;
        //cerr << "BSEARCH FOR POINT " << lowbad << " " << highgood << "\n";
        if (numRow((4096+mid-add)%4096) > 0) highgood = mid;
        else lowbad = mid;
        curr_sz++;
    }
    tl_col = (4096+highgood-add)%4096;

    found(tl_row, tl_col);
    
}
