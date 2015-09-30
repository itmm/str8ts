#include <iostream>

#include "game.h"

int solve(Game &g) {
    if (!g.is_valid()) return 0;

    int row = 0, col = 0;
    char *ch = g.free_cell(col, row);
    if (!ch) {
        return 1;
    }
    int result = 0;
    set orig_row = g.row(row);
    set orig_col = g.col(col);
    set valids = orig_row; valids &= orig_col;
    while (valids) {
        int i = valids.popDigit();
        set d = set::forDigit(i);
        g.row(row) -= d;
        g.col(col) -= d;
        *ch = to_char(i);
        result += solve(g);
        g.row(row) = orig_row;
        g.col(col) = orig_col;
    }
    *ch = ' ';
    return result;
}

int main(int argc, const char * argv[]) {
    Game g(
//        "#2345678I"
//        "9#234567H"
//        "89#234567"
//        "789#23456"
//        "6789#2345"
//        "56789#234"
//        "456789#23"
//        "3456789#2"
//        "23456789A"

        "##   #5 #"
        "# 7     #"
        "8  #5 C2 "
        "  F  I   "
        "##1   2#G"
        "   A 6#  "
        "  #  #   "
        "# 5    8#"
        "B  #9  ##"
    );
    
//    std::cout << "start\n";
//    for (int i = 0; i < 1000; ++i) solve(g);
//    std::cout << "end\n";
    std::cout << solve(g) << " solutions\n";
    
    return 0;
}
