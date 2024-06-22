#include "cube.h"
#include "solver.h"

int main()
{
    srand(time(0));
    
    CubeState state2;
    state2.scramble();
    state2.disp();
    
    Solver solver;
    solver.solve(state2, true);
    for (auto i : solver.moves) std::cout << i << " ";
    std::cout << "\n" << solver.moves.size() << "\n";
    
    solver.state.disp();
  
    return 0;
}
