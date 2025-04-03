#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

using std::ifstream, std::pair, std::string, std::cout, std::endl, std::vector;

int getPoints(double x, double y) {
    double possibleInt, ring = 10*sqrt(pow(x, 2) + pow(y, 2));
    
    // if outside of ring, kill
    if (ring > 10) return 0;

    // if it lands on the line, adjust number
    if (std::modf(ring, &possibleInt) == 0.0 && (x != 0.0 || y != 0.0)) ring--;

    ring = ceil(10 - ring);
    return ring;
}

int main(int argc, char* argv[]) {
    // ifstream file("input.txt");

    string str = "blank";
    getline(std::cin, str);
    int totalShots = std::stoi(str);
    int totalPoints = 0;

    // get inputs
    for (int i = 0; i < totalShots; i++) {
        double x = -1, y = -1;
        getline(std::cin, str);
        
        // find where the space is and grab coords
        for (unsigned int i = 0; i < str.size(); i++) {
            if (str.at(i) == ' ') {
                x = stod(str.substr(0, i));
                y = stod(str.substr(i+1, str.size()-i+1));
            }
        }

        // get point value
        totalPoints += getPoints(x, y);
    }

    cout << totalPoints;
    
    return 0;
}