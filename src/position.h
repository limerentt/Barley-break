#include <iostream>
#include <unordered_set>
#include <queue>
#include <string>
#include <vector>

struct Position {
    uint64_t pos = 0;
    short zero_index = 0;
    // h - is a heuristic of current position
    short h = 0;
    std::string turn = "";

    Position() = default;
    Position(uint64_t pos_): pos(pos_) {}
    ~Position() = default;

    void set_num(short index, short num) {
        for (short i = 0; i < 4; ++i) {
            pos &= ~(static_cast<uint64_t>(1) << (4 * index + i));
        }
        pos += (static_cast<uint64_t>(num) << (4 * index));
    }

    short get_num(uint64_t index) { return short(((pos >> (4 * index)) & 15)); }
};
