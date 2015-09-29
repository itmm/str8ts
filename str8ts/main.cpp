#include <iostream>

#include "game.h"

void solve(Game g) {
    if (!g.is_valid()) return;
    char *ch = g.free_cell();
    if (!ch) {
        std::cout << g << "\n";
        return;
    }
    for (char i = '1'; i <= '9'; ++i) {
        *ch = i;
        solve(g);
    }
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
    
    solve(g);
    
    return 0;
}
