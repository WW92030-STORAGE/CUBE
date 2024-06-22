#include "cube.h"
#include "solver.h"
#include <vector>

void Solver::cross() {
    // CROSS - First align the colors of the top face on the bottom and then one by one swap them up to the top
    bool DEBUG = false;
	Color c = state.UP[1][1];

	while (true) {
        std::vector<bool> solved = state.edges(state.DOWN, c);

        for (int d = 0; d < 4; d++) {
			if (DEBUG) std::cout << "ATTEMPTING TO LOOK AT TOP FACE " << d << "\n";
			if (DEBUG) state.disp();
            if (solved[d]) continue;
            
            // Is the piece on the top face?
            std::vector<bool> ups = state.edges(state.UP, c);

            bool fuckaround = false;
            if (ups[d % 4]) {
                fuckaround = true;
            }
            else if (ups[(d + 3) % 4]) {
                U();
                fuckaround = true;
            }
            else if (ups[(d + 2) % 4]) {
                U(); U();
                fuckaround = true;
            }
            else if (ups[(d + 1) % 4]) {
                U(); U(); U();
                fuckaround = true;
            }
            
            // F R U B L D X Y Z : 0 - 8
            // 0 1 2 3 4 5 6 7 8
            
            if (fuckaround) {
            
            if (d == 0) { // (0, 1)
                L(); L();
            }
            else if (d == 1) { // (1, 2)
                B(); B();
            }
            else if (d == 2) { // (2, 1)
                R(); R();
            }
            else if (d == 3) { // (1, 0)
                F(); F();
            }
            
            }
        }

		if (DEBUG) {
			std::cout << "TOP FACES CHECKED\n";
			state.disp();

		}
        
        // The rest of the unsolved pieces are on the side faces.
        // If a desired piece is on the bottom (i.e. correct position, colors swapped) a special algorithm is applied to resolve it.
        // Otherwise we rotate the bottom face until no already-placed pieces are on that side.
        // Then we rotate the piece to the bottom and resolve.
        // To rotate a piece on the bottom: F' D R'
            
        // This can reduce down to:
        // for each of the side faces:
            // for each desired piece on the side face: rotate bottom and that face until desired piece is on bottom, then F' D R'
        
        solved = state.edges(state.DOWN, c);
		if (DEBUG) std::cout << "RESOLVING SIDE EDGES\n";
		if (DEBUG) state.disp();
    
        if (solved[0] && solved[1] && solved[2] && solved[3]) break;
        
        // F R U B L D X Y Z : 0 - 8
        // 0 1 2 3 4 5 6 7 8
            
        for (int i = 0; i < 4; i++) {
            std::vector<bool> edges = state.edges(state.FRONT, c);
            if (!(edges[0] || edges[1] || edges[2] || edges[3])) {
                Y();
                continue;
            }
            
            while (state.DOWN[1][0] == c) D();
            while (state.FRONT[1][0] != c) F();
                
            // Resolve
                
            for (int xxxxx = 0; xxxxx < 3; xxxxx++) F();
            D();
            for (int xxxxx = 0; xxxxx < 3; xxxxx++) R();

			if (DEBUG) {
				std::cout << "PLACED AN EDGE PIECE ON THE BOTTOM\n";
				state.disp();
			}
            
            Y(); // next face
        }
        
    }
        
    if (DEBUG) std::cout << "PIECES ISOLATED\n";
        
    // Flip the bottom faces to the top to solve the cross.
        
    // F R U B L D X Y Z : 0 - 8
    // 0 1 2 3 4 5 6 7 8
        
    for (int i = 0; i < 4; i++) {
        while (!(state.DOWN[1][0] == c && state.FRONT[1][0] == state.FRONT[1][1])) D();
        F(); F(); Y();
    }
}