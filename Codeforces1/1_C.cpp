#include <iostream>
#include <vector>
// #include <fstream>
#include <string>
// #include <cmath>
// #include <algorithm>
// #include <iomanip>
#include <stdio.h>
#include <cstdint>
 
using std::vector, std::string, std::cout, std::cin;
 
int main(int argc, char* argv[]) {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int T = 0;
    int n = 0;
    int m = 0;
    cin >> T >> n >> m;
    
    vector<uint8_t> cheeps(T, 0);
 
    // get upper cheeps
    int i = 0;
    int begin, end, rainbow;
    for (i = 0; i < n; i++) {
        cin >> begin >> end >> rainbow;
 
        if (begin < 0 || end >= T) continue;
 
        // // cout << "test: " << begin << ", " << end << ", " << rainbow << endl;
        
        // fill cheeps
        for (begin = begin; begin <= end; begin++) {
            if (rainbow == 1) cheeps[begin] = 3;
            else cheeps[begin] = 1;
        }
    }
 
    // get lower cheeps
    for (i = 0; i < m; i++) {
        cin >> begin >> end >> rainbow;
 
        if (begin < 0 || end >= T) continue;
        
        // fill cheeps
        for (begin = begin; begin <= end; begin++) {
            // int count = 0;
            // if (rainbow == 1) count = 3;
            // else count = 1;
 
            // if (count >= cheeps[begin]) cheeps[begin] = count;
            if (rainbow == 1 && 3 >= cheeps[begin]) cheeps[begin] = 3;
            else if (rainbow == 0 && 1 >= cheeps[begin]) cheeps[begin] = 1;
        }
    }
    
    // calculate score
    begin = 0;
    for (i = 0; i < T; i++) {
        begin += cheeps[i];
    }
 
    cout << begin;
}