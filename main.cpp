#include "cube.h"
#include "solver.h"

CubeState cube;

void process(int opcode) {
  if (opcode < 0) {
    for (int i = 0; i < 3; i++) process(abs(opcode));
    return;
  }
  if (opcode >= 10) {
    for (int i = 0; i < 2; i++) process(opcode - 10);
    return;
  }

  if (opcode == 1) cube.F_(); // somehow a built in method is also called F so we rename all instances in this one.
  if (opcode == 2) cube.R_();
  if (opcode == 3) cube.U_();
  if (opcode == 4) cube.B_();
  if (opcode == 5) cube.L_();
  if (opcode == 6) cube.D_();
  if (opcode == 7) cube.X_();
  if (opcode == 8) cube.Y_();
  if (opcode == 9) cube.Z_();
}

int main()
{
    /*
    CubeState state;
    state.F();
    state.F();
    state.B();
    state.B();
    state.disp();
    state.L();
    state.L();
    state.R();
    state.R();
    state.disp();
    state.U();
    state.U();
    state.D();
    state.D();
    state.disp();
    
    std::cout << state.isSolved() << "\n";
    
    for (int i = 0; i < 3; i++) {
    
    state.R();
    state.L();
    state.L();
    state.L();
    state.U();
    state.D();
    state.D();
    state.D();
    
    }
    
    state.X();
    state.disp();
    state.Y();
    state.disp();
    state.Z();
    state.disp();
    
    std::cout << state.isSolved() << "\n";
    
    */
    
    srand(time(0));
    
    cube.scramble();
    cube.disp();
    
    Solver solver;
    solver.solve(CubeState(cube), false);
    for (auto i : solver.moves) std::cout << i << " ";
    std::cout << "\n" << solver.moves.size() << "\n";
    
    solver.state.disp();
    
    cube.disp();
    
    for (int i = 0; i < solver.moves.size(); i++) {
        process(solver.moves[i]);
        // cube.disp();
    }
    
    cube.disp();

    return 0;
}
