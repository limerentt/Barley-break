#include "../src/algorithm.h"

int main() {
    Position start, finish;

    std::cout << "Input a starting position:\n\n";

    short num_of_start_inversions = set_extreme_positions(start, finish);
    // check if the ending position is reachable
    if (!end_is_reachable(start, num_of_start_inversions)) {
        std::cout << "Winning strategy is not reachable";
        return 0;
    }

    std::string path = find_path(start, finish);
    
    std::cout << "\nYou can get things done in " << path.size() << " moves:\n\n";
    std::cout << path;
}
