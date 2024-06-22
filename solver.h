#ifndef SOLVER_H
#define SOLVER_H

#include "cube.h"
#include <vector>
#include <algorithm>

class Solver {
    public:
    CubeState original;
    CubeState state;
    
    // F R U B L D X Y Z
    // 1 2 3 4 5 6 7 8 9
    // Primes are negative numbers. Doubles are 11 - 19
    
    
    std::vector<int> moves;
    
    void F() {
        state.F();
        moves.push_back(1);
    }
    
    void R() {
        state.R();
        moves.push_back(2);
    }
    
    void U() {
        state.U();
        moves.push_back(3);
    }
    
    void B() {
        state.B();
        moves.push_back(4);
    }
    
    void L() {
        state.L();
        moves.push_back(5);
    }
    
    void D() {
        state.D();
        moves.push_back(6);
    }
    
    void X() {
        state.X();
        moves.push_back(7);
    }
    
    void Y() {
        state.Y();
        moves.push_back(8);
    }
    
    void Z() {
        state.Z();
        moves.push_back(9);
    }
    
    // Solves the cube using a modified CFOP algorithm (aka. the Beginners Method).
    
    int ex[4] = {00, 01, 02, 01};
    int ey[4] = {01, 02, 01, 00};
    
    int cx[4] = {00, 00, 02, 02};
    int cy[4] = {00, 02, 02, 00};
    
    // In every single method we are solving for the top 2 faces. This means that during Cross and F2L the upper faces hold the solution.
    // And during the last layer the cube is rotated 180 degrees so that the first 2 layers are on the bottom.
    
    void cross();
    
    void F2L();
    
    void OLL();
    
    void PLL();
    
    void aperm();
    
    void manage() {
        std::vector<int> blip;
        for (int i = moves.size() - 1; i >= 0; i--) {
            if (i >= 3 && moves[i] == moves[i - 1] && moves[i] == moves[i - 2] && moves[i] == moves[i - 3]) {
                i -= 3;
                continue;
            }
            else if (i >= 2 && moves[i] == moves[i - 1] && moves[i] == moves[i - 2]) {
                i -= 2;
                blip.push_back(-1 * moves[i]);
                continue;
            }
            else if (i >= 1 && moves[i] == moves[i - 1]) {
                i--;
                blip.push_back(10 + moves[i]);
                continue;
            }
            else blip.push_back(moves[i]);
        }
        
        std::reverse(blip.begin(), blip.end());
        moves = blip;
    }
    
    void solve(CubeState state2, bool verbose = false) {
        original = CubeState(state2);
        state = CubeState(state2);
        
        // Solve the first 2 layers, assuming the color of choice is the uppermost face.
        
        cross();
        
        if (verbose) std::cout << "CROSS STEP DONE\n";
        F2L();
        if (verbose) std::cout << "F2L STEP DONE\n";
        
        // Rotate the cube so the last layer is on top
        
        X(); X();
        
        OLL();
        
        if (verbose) std::cout << "OLL STEP DONE\n";
        
        PLL();
        
        manage();
    }
};

#endif