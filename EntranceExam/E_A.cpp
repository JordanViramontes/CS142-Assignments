#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

using std::ifstream, std::pair, std::string, std::cout, std::endl, std::vector;

int main(int argc, char* argv[]) {
    // ifstream file("input.txt");

    // set up data pairs for each house
    pair<string, int> Gry ("Gryffindor", 0), Huf ("Hufflepuff", 0), Rav ("Ravenclaw", 0), Sly ("Slytherin", 0);

    string str = "blank";
    while (getline(std::cin, str)) {
        
        // first line
        if (str == "blank") {
            str = "notblank";
            continue;
        }

        // normal score
        if (str == "Gryffindor") Gry.second += 10;
        else if (str == "Hufflepuff") Huf.second += 10;
        else if (str == "Ravenclaw") Rav.second += 10; 
        else if (str == "Slytherin") Sly.second += 10;

        // golden snitch
        string snitch = " caught the Golden Snitch";
        if (str == "Gryffindor" + snitch) {
            Gry.second += 150;
            break;
        } else if (str == "Hufflepuff" + snitch) {
            Huf.second += 150;
            break;
        } else if (str == "Ravenclaw" + snitch) {
            Rav.second += 150;
            break;
        } else if (str == "Slytherin" + snitch) {
            Sly.second += 150;
            break;
        }
    }

    // vector for sorting
    vector<pair<string, int>> scores = { Gry, Huf, Rav, Sly };

    // overload the sort function so that we can compare the 2nd element in pair
    std::sort(scores.begin(), scores.end(), [](const std::pair<string,int> &left, const std::pair<string,int> &right) {
        return left.second > right.second;
    });

    // output
    if (scores.at(0).second == scores.at(1).second) // Tie
        cout << "Tie\n" << scores.at(0).second << "-" << scores.at(1).second;
    else cout << scores.at(0).first << " wins\n" << scores.at(0).second << "-" << scores.at(1).second;

    return 0;
}