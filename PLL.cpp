#include "cube.h"
#include "solver.h"
#include <vector>

void Solver::aperm() {
    R(); B(); B(); B(); R(); F(); F(); 
    R(); R(); R(); B(); R(); F(); F(); R(); R();
}

void Solver::PLL() {
	bool DEBUG = false;
    while (true) {
	if (DEBUG) state.disp();
    int chestplates = 0; // Named after the crafting recipe for the aforementioned object in Minecraft.
    for (int i = 0; i < 4; i++) {
        if (state.FRONT[0][2] == state.FRONT[2][2]) {
            chestplates++;
        }
        U();
    }
    if (chestplates == 0) {
        aperm();
        continue;
    }
    
    if (chestplates == 1) {
        while (state.FRONT[0][2] != state.FRONT[2][2]) U();
        aperm();
        continue;
    }
    
    // There are either 0 1 or 4 chestplates. The next case handles 4.

	if (state.FRONT[1][2] == state.FRONT[2][2] && state.RIGHT[1][2] == state.RIGHT[2][2] && state.BACK[1][2] == state.BACK[2][2] && state.LEFT[1][2] == state.LEFT[2][2]) {
		while (state.FRONT[1][2] != state.FRONT[1][1]) U();
		return;
	}
    
    if (state.FRONT[1][2] == state.BACK[2][2] && state.BACK[1][2] == state.FRONT[2][2] && state.LEFT[1][2] == state.RIGHT[2][2] && state.RIGHT[1][2] == state.LEFT[2][2]) {
        R(); R(); L(); L(); X(); X(); U();
        R(); R(); L(); L(); X(); X(); U(); U();
        R(); R(); L(); L(); X(); X(); U();
        R(); R(); L(); L(); X(); X(); 
        while (state.FRONT[1][2] != state.FRONT[1][1]) U();
    }
    int disparities = 0;
    for (int i = 0; i < 4; i++) {
        if (state.FRONT[1][2] != state.FRONT[0][2]) disparities++;
        U();
    }
    
    if (disparities == 3) {
        while (state.BACK[1][2] != state.BACK[2][2]) U();
        if (state.RIGHT[1][2] == state.LEFT[2][2]) {
            R(); U(); U(); U();
            R(); U(); R(); U();
            R(); U(); U(); U();
            R(); R(); R(); U(); U(); U();
            R(); R();
        }
        else {
            L(); L(); L(); U();
            L(); L(); L(); U(); U(); U();
            L(); L(); L(); U(); U(); U();
            L(); L(); L(); U(); 
            L(); U(); L(); L();
        }
        
        while (state.FRONT[1][2] != state.FRONT[1][1]) U();
    }
    else {
        while (state.FRONT[1][2] != state.RIGHT[0][2]) U();
        R(); R(); L(); L(); X(); X(); U();
        R(); R(); L(); L(); X(); X(); U();
        R(); R(); R(); L(); X(); U(); U();
        R(); R(); L(); L(); X(); X(); U(); U();
        R(); R(); R(); L(); X();
        while (state.FRONT[1][2] != state.FRONT[1][1]) U();
    }
    
    return;
    
    }
}