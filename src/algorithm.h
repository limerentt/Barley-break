#include "./position.h"


void linear_align(Position& tag) {
    for (short i = 0; i < 4; ++i) {
        for (short j = 0; j < 3; ++j) {
            if ((tag.get_num(4 * i + j) - 1) / 4 != i || tag.get_num(4 * i + j) == 0) continue;
            for (short k = j + 1; k < 4; ++k) {
                if ((tag.get_num(4 * i + k) - 1) / 4 != i || tag.get_num(4 * i + k) == 0) continue;
                if (tag.get_num(4 * i + k) < tag.get_num(4 * i + j)) tag.h += 2;
            }
        }
    }
    for (short i = 0; i < 4; ++i) {
        for (short j = 0; j < 3; ++j) {
            if ((tag.get_num(4 * j + i) - 1) % 4 != i || tag.get_num(4 * j + i) == 0) continue;
            for (short k = j + 1; k < 4; ++k) {
                if ((tag.get_num(4 * k + i) - 1) % 4 != i || tag.get_num(4 * k + i) == 0) continue;
                if (tag.get_num(4 * k + i) < tag.get_num(4 * j + i)) tag.h += 2;
            }
        }
    }
    if (tag.get_num(0) != 1 && (tag.get_num(1) == 2 && tag.get_num(4) == 5)) tag.h += 2;
    if (tag.get_num(3) != 4 && (tag.get_num(2) == 3 && tag.get_num(7) == 8)) tag.h += 2;
    if (tag.get_num(12) != 13 && (tag.get_num(8) == 9 && tag.get_num(13) == 14)) tag.h += 2;
}

short set_extreme_positions(Position& start, Position& finish) {
    short read_tag;
    for (short i = 0; i < 16; ++i) {
        std::cin >> read_tag;
        start.set_num(i, read_tag);
        finish.set_num(i, (i + 1) % 16);
    }
    finish.zero_index = 15;
    finish.h = 0;
    short num_of_start_inversions = 0;

    for (short i = 0; i < 16; ++i) {
        if (start.get_num(i)) {
            start.h += abs(start.get_num(i) % 4 - i % 4) + abs(start.get_num(i) / 4 - i / 4);
            for (short j = 0; j < i; ++j) {
                if (start.get_num(j) > start.get_num(i)) ++num_of_start_inversions;
            }
        } else {
            start.zero_index = i;
        }
    }
    linear_align(start);
    return num_of_start_inversions;
}

bool end_is_reachable(Position& start, short num_of_start_inversions) {
    return (num_of_start_inversions + start.zero_index / 4) % 2 != 0;
}

void add_tag_to_queue(Position& son, Position& vertex, char direction) {
    if (direction == 'U') {
        son.set_num(vertex.zero_index, vertex.get_num(vertex.zero_index + 4));
        son.set_num(vertex.zero_index + 4, 0);
        son.zero_index += 4;
        son.h = 0;
    }
    if (direction == 'D') {
        son.set_num(vertex.zero_index, vertex.get_num(vertex.zero_index - 4));
        son.set_num(vertex.zero_index - 4, 0);
        son.zero_index -= 4;
        son.h = 0;
    }
    if (direction == 'L') {
        son.set_num(vertex.zero_index, vertex.get_num(vertex.zero_index + 1));
        son.set_num(vertex.zero_index + 1, 0);
        ++son.zero_index;
        son.h = 0;
    }
    if (direction == 'R') {
        son.set_num(vertex.zero_index, vertex.get_num(vertex.zero_index - 1));
        son.set_num(vertex.zero_index - 1, 0);
        --son.zero_index;
        son.h = 0;
    }
    linear_align(son);
    for (short i = 0; i < 16; ++i) {
        if (son.get_num(i))
            son.h += abs((son.get_num(i) - 1) % 4 - i % 4) + abs((son.get_num(i) - 1) / 4 - i / 4);
    }
    son.turn += direction;
}

std::string find_path(Position& start, Position& finish) {
    auto comp = [](const Position& a, const Position& b) {
        return (a.h * 1.015 + a.turn.size() > b.h * 1.015 + b.turn.size());
    };
    std::priority_queue<Position, std::vector<Position>, decltype(comp)> choices(comp);
    std::unordered_set<uint64_t> used;
    choices.push(start);

    while (!choices.empty()) {
        Position vertex(choices.top());
        choices.pop();
        if (used.find(vertex.pos) != used.end()) continue;           
        used.insert(vertex.pos);

        if (vertex.pos == finish.pos) {
            return vertex.turn;
        }

        Position son = vertex;
        if (vertex.zero_index / 4 != 3) {
            son = vertex;
            add_tag_to_queue(son, vertex, 'U');
            choices.push(son);
        }
        if (vertex.zero_index / 4 != 0) {
            son = vertex;
            add_tag_to_queue(son, vertex, 'D');
            choices.push(son);
        }
        if (vertex.zero_index % 4 != 3) {
            son = vertex;
            add_tag_to_queue(son, vertex, 'L');
            choices.push(son);
        }
        if (vertex.zero_index % 4 != 0) {
            son = vertex;
            add_tag_to_queue(son, vertex, 'R');
            choices.push(son);
        }
    }
}
