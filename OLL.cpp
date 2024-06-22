#include "cube.h"
#include "solver.h"
#include <vector>

void Solver::OLL() {
	bool DEBUG = true;
    Color c = state.UP[1][1];
    while (true) {
    std::vector<bool> correctly = state.edges(state.UP, c);
    int sum = 0;
    for (int i = 0; i < 4; i++) sum += (correctly[i]) ? (1<<(i % 2)) : 0;
    if (sum == 6) break;
    else if (sum == 0) {
        F(); R(); U(); R(); R(); R(); U(); U(); U(); F(); F(); F();
    }
    else if (sum % 2 == 0) {
        while (state.UP[0][1] != c) U();
        F(); R(); U(); R(); R(); R(); U(); U(); U(); F(); F(); F();
    }
    else if (sum % 2 == 1) {
        while ((state.UP[1][0] != c) || (state.UP[2][1] != c)) {
            U();
        }
        F(); R(); U(); R(); R(); R(); U(); U(); U(); F(); F(); F();
    }
    }
    
    if (DEBUG) state.disp();
    
    while (true) {
    
    std::vector<bool> correctly = state.corners(state.UP, c);
    int sum = 0;
    int count = 0;
    for (int i = 0; i < 4; i++) {
        sum += (correctly[i]) ? (1<<(i % 2)) : 0;
        count += correctly[i];
    }
    if (DEBUG) std::cout << sum << " " << count << "\n";
    if (DEBUG) state.disp();
    
    if (count == 4) return;
    else if (count == 1) {
        while (state.UP[0][2] != c) U();
        if (state.FRONT[2][2] == c) {
            U(); U(); U(); R(); U(); R(); R(); R(); U(); R(); U(); U(); R(); R(); R();
        }
        else {
            U(); U(); L(); L(); L(); U(); U(); U(); L(); U(); U(); U(); L(); L(); L(); U(); U(); L();
        }
    }
    else if (count == 2) {
        if (sum % 2 == 0) {
            while (state.UP[2][0] != c || state.FRONT[0][2] != c) U();
            F(); R(); R(); R(); F(); F(); F(); L(); X(); U(); R(); U(); U(); U(); X(); X(); X(); L(); L(); L(); 
        }
        else {
            while (state.UP[2][0] != c || state.UP[2][2] != c) U();
            if (state.FRONT[0][2] == c) {
				L(); X(); U(); R(); R(); R(); U(); U(); U(); X(); X(); X(); L(); L(); L(); F(); R(); F(); F(); F();
            }
            else { // In the front
				U(); U(); U();
                R(); R(); D(); R(); R(); R(); U(); U(); R(); D(); D(); D(); R(); R(); R(); U(); U(); R(); R(); R();
            }
        }
    }
    else {
        while (state.LEFT[0][2] != c) U();
        if (state.RIGHT[0][2] == c) {
            R(); U(); R(); R(); R(); U(); R(); U(); U(); U(); R(); R(); R(); U(); R(); U(); U(); R(); R(); R();
        }
        else {
            R(); U(); U(); R(); R(); U(); U(); U(); R(); R(); U(); U(); U(); R(); R(); U(); U(); R();
        }
    }
    }
}