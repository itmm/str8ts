#include "game.h"

#include <cstring>
#include <iostream>

inline void add_set(set &s, const char *row, int offset) {
    for (int i = 0; i < 9; ++i, row += offset) {
        s -= set::forDigit(digit(*row));
    }
}

Game::Game(const char *data) {
    memcpy(_data, data, 9 * 9);
    
    add_set(_cols[0], _data + 0 * 1, 9);
    add_set(_cols[1], _data + 1 * 1, 9);
    add_set(_cols[2], _data + 2 * 1, 9);
    add_set(_cols[3], _data + 3 * 1, 9);
    add_set(_cols[4], _data + 4 * 1, 9);
    add_set(_cols[5], _data + 5 * 1, 9);
    add_set(_cols[6], _data + 6 * 1, 9);
    add_set(_cols[7], _data + 7 * 1, 9);
    add_set(_cols[8], _data + 8 * 1, 9);
    
    add_set(_rows[0], _data + 0 * 9, 1);
    add_set(_rows[1], _data + 1 * 9, 1);
    add_set(_rows[2], _data + 2 * 9, 1);
    add_set(_rows[3], _data + 3 * 9, 1);
    add_set(_rows[4], _data + 4 * 9, 1);
    add_set(_rows[5], _data + 5 * 9, 1);
    add_set(_rows[6], _data + 6 * 9, 1);
    add_set(_rows[7], _data + 7 * 9, 1);
    add_set(_rows[8], _data + 8 * 9, 1);
}

char *Game::free_cell(int &col, int &row) {
    char *end = _data + 9 * 9;
    int i = 0;
    for (char *cur = _data; cur != end; ++cur, ++i) {
        if (is_free(*cur)) {
            col = i % 9;
            row = i / 9;
            return cur;
        }
    }
    return nullptr;
}

inline bool is_valid_row(const char *row, int offset) {
    set found(0);
    int min_row = 10;
    int max_row = 0;
    int row_size = 0;
    
    for (int i = 0; i < 9; ++i, row += offset) {
        int d = digit(*row);
        if (d) {
            set tmp = found;
            tmp &= set::forDigit(d);
            if (tmp) return false;
            found |= set::forDigit(d);
        }

        if (is_blocked(*row)) {
            if (max_row - min_row + 1 > row_size) return false;
            
            min_row = 10;
            max_row = 0;
            row_size = 0;
        } else {
            if (d) {
                if (min_row > d) min_row = d;
                if (max_row < d) max_row = d;
            }
            ++row_size;
        }
    }
    
    if (max_row - min_row + 1 > row_size) return false;

    return true;
}

bool Game::is_valid() {
    if (! is_valid_row(_data + 0 * 1, 9)) return false;
    if (! is_valid_row(_data + 1 * 1, 9)) return false;
    if (! is_valid_row(_data + 2 * 1, 9)) return false;
    if (! is_valid_row(_data + 3 * 1, 9)) return false;
    if (! is_valid_row(_data + 4 * 1, 9)) return false;
    if (! is_valid_row(_data + 5 * 1, 9)) return false;
    if (! is_valid_row(_data + 6 * 1, 9)) return false;
    if (! is_valid_row(_data + 7 * 1, 9)) return false;
    if (! is_valid_row(_data + 8 * 1, 9)) return false;
    
    if (! is_valid_row(_data + 0 * 9, 1)) return false;
    if (! is_valid_row(_data + 1 * 9, 1)) return false;
    if (! is_valid_row(_data + 2 * 9, 1)) return false;
    if (! is_valid_row(_data + 3 * 9, 1)) return false;
    if (! is_valid_row(_data + 4 * 9, 1)) return false;
    if (! is_valid_row(_data + 5 * 9, 1)) return false;
    if (! is_valid_row(_data + 6 * 9, 1)) return false;
    if (! is_valid_row(_data + 7 * 9, 1)) return false;
    if (! is_valid_row(_data + 8 * 9, 1)) return false;
    
    return true;
}

bool Game::is_complete() {
    int row = 0, col = 0;
    return !free_cell(row, col) && is_valid();
}

std::ostream &operator<<(std::ostream &out, const Game &game) {
    for (int y = 0; y < 9; ++y) {
        out << "+---+---+---+---+---+---+---+---+---+\n";
        for (int x = 0; x < 9; ++x) {
            char ch = game(x, y);
            if (is_blocked(ch)) {
                out << "|###";
            } else {
                out << "|   ";
            }
        }
        out << "|\n";
        for (int x = 0; x < 9; ++x) {
            char ch = game(x, y);
            if (is_blocked(ch)) {
                if (ch == '#') {
                    out << "|###";
                } else {
                    out << "|[" << digit(ch) << "]";
                }
            } else {
                out << "| " << ch << " ";
            }
        }
        out << "|\n";
        for (int x = 0; x < 9; ++x) {
            char ch = game(x, y);
            if (is_blocked(ch)) {
                out << "|###";
            } else {
                out << "|   ";
            }
        }
        out << "|\n";
    }
    out << "+---+---+---+---+---+---+---+---+---+\n";
    return out;
}
