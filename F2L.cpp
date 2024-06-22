#include "cube.h"
#include "solver.h"
#include <vector>

void Solver::F2L() {
    bool DEBUG = false;
    Color c = state.UP[1][1];
        
        // Solve the first 2 layers, assuming the cross is already solved. This one is a bit trickier and relies on a lot of casework.
        
        while (true) {
        
            std::vector<bool> wellplaced = {true, true, true, true};
            std::vector<bool> edgeplaced = {true, true, true, true};
            if (state.UP[0][0] != c || state.FRONT[0][2] != state.FRONT[1][1] || state.LEFT[0][2] != state.LEFT[1][1]) wellplaced[0] = false;
            if (state.UP[0][2] != c || state.LEFT[2][2] != state.LEFT[1][1] || state.BACK[0][2] != state.BACK[1][1]) wellplaced[1] = false;
            if (state.UP[2][2] != c || state.BACK[2][2] != state.BACK[1][1] || state.RIGHT[2][2] != state.RIGHT[1][1]) wellplaced[2] = false;
            if (state.UP[2][0] != c || state.FRONT[2][2] != state.FRONT[1][1] || state.RIGHT[0][2] != state.RIGHT[1][1]) wellplaced[3] = false;
            if (state.FRONT[0][1] != state.FRONT[1][1] || state.LEFT[0][1] != state.LEFT[1][1]) edgeplaced[0] = false;
            if (state.LEFT[2][1] != state.LEFT[1][1] || state.BACK[0][1] != state.BACK[1][1]) edgeplaced[1] = false;
            if (state.BACK[2][1] != state.BACK[1][1] || state.RIGHT[2][1] != state.RIGHT[1][1]) edgeplaced[2] = false;
            if (state.RIGHT[0][1] != state.RIGHT[1][1] || state.FRONT[2][1] != state.FRONT[1][1]) edgeplaced[3] = false;
            
        if (wellplaced[0] && wellplaced[1] && wellplaced[2] && wellplaced[3] && edgeplaced[0] && edgeplaced[1] && edgeplaced[2] && edgeplaced[3]) break;
        
        // Look in the top layer for well placed corners
        
        // The desired pieces are always in the front top right. We rotate the cube each iteration to maintain orientation.
        for (int d = 3; d >= 0; d--) {
            while (true) {
                // if wellplaced[3]
                if (state.UP[2][0] == c && state.FRONT[2][2] == state.FRONT[1][1] && state.RIGHT[0][2] == state.RIGHT[1][1]) {
                    // if edgeplaced[3]
                    if (state.FRONT[2][1] == state.FRONT[1][1] && state.RIGHT[0][1] == state.RIGHT[1][1]) break; // nothing to do
                    
                    int edgeonbottom = 0;
                    
                    for (int x = 0; x < 4; x++) { // Attempt to locate the edge on the bottom face.
                        if (state.FRONT[1][0] == state.FRONT[1][1] && state.DOWN[1][0] == state.RIGHT[1][1]) { // Piece is aligned
                            edgeonbottom = 1;
                            break;
                        }
                        if (state.FRONT[1][0] == state.RIGHT[1][1] && state.DOWN[1][0] == state.FRONT[1][1]) { // Piece is mismatched
                            edgeonbottom = 2;
                            break;
                        }
                        D();
                    }
                    
                    if (DEBUG) std::cout << ">!!!" << edgeonbottom << "\n";
                    if (DEBUG) state.disp();
                    
                    // F R U B L D X Y Z : 0 - 8
                    // 0 1 2 3 4 5 6 7 8
                    
                    if (edgeonbottom == 1) {
                        for (int i = 0; i < 3; i++) D();
                        for (int i = 0; i < 3; i++) R();
                        D(); R();
                        for (int i = 0; i < 3; i++) F();
                        R(); F();
                        for (int i = 0; i < 3; i++) R();
                        continue;
                    }
                    else if (edgeonbottom == 2) {
                        D(); D(); F(); D();
                        for (int i = 0; i < 3; i++) F();
                        for (int i = 0; i < 3; i++) D();
                        for (int i = 0; i < 3; i++) R();
                        for (int i = 0; i < 3; i++) D();
                        R();
                        continue;
                    }
                    else {
                        // If the offending edge is on the front side you move it to the bottom and take care of it later
                        bool edgeonfront = false;
                        if (state.FRONT[0][1] == state.FRONT[1][1] && state.LEFT[0][1] == state.RIGHT[1][1]) edgeonfront = true;
                        if (state.FRONT[0][1] == state.RIGHT[1][1] && state.LEFT[0][1] == state.FRONT[1][1]) edgeonfront = true;
                        if (edgeonfront) {
                            for (int i = 0; i < 3; i++) F();
                            D();
                            F();
                        }
                        
                        bool edgeonright = false;
                        if (state.RIGHT[2][1] == state.FRONT[1][1] && state.BACK[2][1] == state.RIGHT[1][1]) edgeonright = true;
                        if (state.RIGHT[2][1] == state.RIGHT[1][1] && state.BACK[2][1] == state.FRONT[1][1]) edgeonright = true;
                        if (edgeonright) {
                            R();
                            D();
                            for (int i = 0; i < 3; i++) R();
                        }
                        
                        bool flippededge = (state.FRONT[2][1] == state.RIGHT[1][1] && state.RIGHT[0][1] == state.FRONT[1][1]);
                        if (flippededge) {
                            for (int i = 0; i < 3; i++) R();
                            D(); R(); D(); F();
                            for (int i = 0; i < 3; i++) D();
                            for (int i = 0; i < 3; i++) F();
                        }
                        
                        bool cursededge = false;
                        if (state.BACK[0][1] == state.FRONT[1][1] && state.LEFT[2][1] == state.RIGHT[1][1]) cursededge = true;
                        if (state.BACK[0][1] == state.RIGHT[1][1] && state.LEFT[2][1] == state.FRONT[1][1]) cursededge = true;
                        if (cursededge) {
                            L(); L(); L(); D(); L();
                        }
                        
                        if (DEBUG) std::cout << flippededge << " " << edgeonfront << " " << edgeonright << " " << cursededge << "\n";
                    } // End of else statement
                } // End of if wellplaced[3]
                else { // Corner is not well placed we need to FIND IT
                    if (DEBUG) std::cout << "CORNER NOT WELL PLACED NEED TO FIND\n";
                    if (DEBUG) state.disp();
                    // These first set of conditions are where the corner is in the top layer in which we reduce to an already solved problem
                    std::set<Color> desired = {state.FRONT[1][1], state.RIGHT[1][1], state.UP[1][1]};
                    std::set<Color> c0 = {state.FRONT[2][2], state.RIGHT[0][2], state.UP[2][0]};
                    bool cornerattop = false;
                    if (c0 == desired) { // Corner exists in wrong orientation. All other cases reduce to this one.
                        cornerattop = true;
                        while (state.UP[2][0] != state.UP[1][1]) {
                            R(); R(); R(); D(); R(); 
                            D(); D(); D(); R(); R(); R(); D(); R();
                        }
                    }
                    std::set<Color> c1 = {state.FRONT[0][2], state.LEFT[0][2], state.UP[0][0]};
                    if (c1 == desired) { // Corner is left of spawn
                        cornerattop = true;
                        L(); D(); L(); L(); L();
                        D(); D(); D(); R(); R(); R(); D(); R();
                    }
                    
                    std::set<Color> c2 = {state.LEFT[2][2],state.BACK[0][2], state.UP[0][2]};
                    if (c2 == desired) { // Corner opposes spawn
                        cornerattop = true;
                        B(); D(); B(); B(); B(); 
                        R(); R(); R(); D(); R();
                    }
                    std::set<Color> c3 = {state.RIGHT[2][2], state.BACK[2][2], state.UP[2][2]};
                    if (c3 == desired) { // corner is on the right
                        cornerattop = true;
                        B(); B(); B(); D(); D(); B();
                        R(); R(); R(); D(); R();
                    }
                    
                    // The next conditions deal with if the corner is in the bottom.
                    
                    if (!cornerattop) {
                        if (DEBUG) std::cout << "CORNER ON BOTTOM\n";
                    
                    for (int i = 0; i < 8; i++) {
                        std::set<Color> c4 = {state.FRONT[2][0], state.RIGHT[0][0], state.DOWN[2][0]};
                        if (c4 == desired) break;
                        D();
                    }
                    D(); D(); D(); R(); R(); R(); D(); R();
                    } // End of bottom corner
                    if (DEBUG) std::cout << "PLACED CORNER\n";
                    if (DEBUG) state.disp();
                } // End of not well placed corner calculation
            } // End of while true
                
            state.Y();
            moves.push_back(7);
        } // End of main loop (4 iterations)
    }
}
