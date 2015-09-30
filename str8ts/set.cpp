#include "set.h"

#include <cassert>

static int masks[] = {
    0x0000, 0x0001, 0x0002, 0x0004, 0x0008,
    0x0010, 0x0020, 0x0040, 0x0080, 0x0100
};

static set sets[] = {
    set(masks[0]), set(masks[1]), set(masks[2]), set(masks[3]), set(masks[4]),
    set(masks[5]), set(masks[6]), set(masks[7]), set(masks[8]), set(masks[9])
};

set::set() : _mask(
    masks[1] + masks[2] + masks[3] + masks[4] +
    masks[5] + masks[6] + masks[7] + masks[8] + masks[9]
) {}

set &set::forDigit(int digit) {
    assert(digit >= 0 && digit <= 9);
    return sets[digit];
}

int set::popDigit() {
    assert(_mask != 0);
    
    if (_mask & (masks[1] | masks[2] | masks[3])) {
        if (_mask & masks[1]) { _mask -= masks[1]; return 1; }
        else if (_mask & masks[2]) { _mask -= masks[2]; return 2; }
        else { _mask -= masks[3]; return 3; }
    } else if (_mask & (masks[4] | masks[5] | masks[6])) {
        if (_mask & masks[4]) { _mask -= masks[4]; return 4; }
        else if (_mask & masks[5]) { _mask -= masks[5]; return 5; }
        else { _mask -= masks[6]; return 6; }
    } else {
        if (_mask & masks[7]) { _mask -= masks[7]; return 7; }
        else if (_mask & masks[8]) { _mask -= masks[8]; return 8; }
        else { _mask -= masks[9]; return 9; }
    }
}

std::ostream &operator<<(std::ostream &out, const set &s) {
    for (int i = 1; i <= 9; ++i) {
        set x = s; x &= sets[i];
        if (x) { out << i; } else { out << "-"; }
    }
    return out;
}
