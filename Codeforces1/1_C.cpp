#include <iostream>
#include <vector>
// #include <fstream>
#include <string>
// #include <cmath>
// #include <algorithm>
// #include <iomanip>
#include <stdio.h>

using std::vector, std::string, std::cout;

int main(int argc, char* argv[]) {
    string str = "";

    int T = 0;
    int n = 0;
    int m = 0;
    scanf("%d %d %d", &T, &n, &m);

    int* cheeps = new int[T](); 
    for (int i = 0; i < T; i++) {
        cheeps[i] = 0;
    }

    // get upper cheeps
    for (int i = 0; i < n; i++) {
        int begin, end, rainbow;
        scanf("%d %d %d", &begin, &end, &rainbow);

        // cout << "test: " << begin << ", " << end << ", " << rainbow << endl;
        
        // fill cheeps
        for (int j = begin; j <= end; j++) {
            if (rainbow == 1) cheeps[j] = 3;
            else cheeps[j] = 1;
        }
    }

    // get lower cheeps
    for (int i = 0; i < m; i++) {
        int begin, end, rainbow;
        scanf("%d %d %d", &begin, &end, &rainbow);
        
        // fill cheeps
        for (int j = begin; j <= end; j++) {
            int count = 0;
            if (rainbow == 1) count = 3;
            else count = 1;

            if (count >= cheeps[j]) cheeps[j] = count;
        }
    }
    
    // calculate score
    int totalScore = 0;
    for (int i = 0; i < T; i++) {
        totalScore += cheeps[i];
    }

    cout << totalScore;

    delete[] cheeps;
}