#include "game.h"

#include <iostream>

char *Game::free_cell() {
    char *end = _data + 9 * 9;
    for (char *cur = _data; cur != end; ++cur) {
        if (is_free(*cur)) return cur;
    }
    return nullptr;
}

bool Game::is_valid_row(const char *row, int offset) {
    static int bits[] = {
        0x0000, 0x0001, 0x0002, 0x0004, 0x0008,
        0x0010, 0x0020, 0x0040, 0x0080, 0x0100
    };

    int found = 0;
    int min_row = 10;
    int max_row = 0;
    int row_size = 0;
    
    for (int i = 0; i < 9; ++i, row += offset) {
        if (is_blocked(*row)) {
            int d = digit(*row);
            if (d) {
                if (found & bits[d]) return false;
                found |= bits[d];
                
            }
                
            if (max_row - min_row + 1 > row_size) {
                return false;
            }
            
            min_row = 10;
            max_row = 0;
            row_size = 0;
        } else {
            int d = digit(*row);
            if (d) {
                if (found & bits[d]) return false;
                found |= bits[d];
                
                if (min_row > d) min_row = d;
                if (max_row < d) max_row = d;
            }
            ++row_size;
        }
    }
    
    if (max_row - min_row + 1 > row_size) {
        return false;
    }

    return true;
}

bool Game::is_valid() {
    if (!is_valid_row(_data + 0 * 1, 9)) return false;
    if (!is_valid_row(_data + 1 * 1, 9)) return false;
    if (!is_valid_row(_data + 2 * 1, 9)) return false;
    if (!is_valid_row(_data + 3 * 1, 9)) return false;
    if (!is_valid_row(_data + 4 * 1, 9)) return false;
    if (!is_valid_row(_data + 5 * 1, 9)) return false;
    if (!is_valid_row(_data + 6 * 1, 9)) return false;
    if (!is_valid_row(_data + 7 * 1, 9)) return false;
    if (!is_valid_row(_data + 8 * 1, 9)) return false;
    
    if (!is_valid_row(_data + 0 * 9, 1)) return false;
    if (!is_valid_row(_data + 1 * 9, 1)) return false;
    if (!is_valid_row(_data + 2 * 9, 1)) return false;
    if (!is_valid_row(_data + 3 * 9, 1)) return false;
    if (!is_valid_row(_data + 4 * 9, 1)) return false;
    if (!is_valid_row(_data + 5 * 9, 1)) return false;
    if (!is_valid_row(_data + 6 * 9, 1)) return false;
    if (!is_valid_row(_data + 7 * 9, 1)) return false;
    if (!is_valid_row(_data + 8 * 9, 1)) return false;
    return true;
}

bool Game::is_complete() {
    return !free_cell() && is_valid();
}

std::ostream &operator<<(std::ostream &out, const Game &game) {
    for (int y = 0; y < 9; ++y) {
        for (int x = 0; x < 9; ++x) {
            char ch = game(x, y);
            if (is_blocked(ch)) ch = '#';
            out << ch;
        }
        out << "\n";
    }
    return out;
}
