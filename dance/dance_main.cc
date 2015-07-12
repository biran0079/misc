#include "exact_cover_puzzle_maker.h"
#include "dance.h"
#include <vector>
using namespace std;

int main() {
  vector<vector<int> > a = {
    {0, 0, 1, 0, 1, 1, 0},
    {1, 0, 0, 1, 0, 0, 1},
    {0, 1, 1, 0, 0, 1, 0},
    {1, 0, 0, 1, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 1},
    {0, 0, 0, 1, 1, 0, 1},
  };
  ExactCoverPuzzleMaker maker;
  PrintSolution printSolution;
  DLX solver(true, &printSolution);
  Node* root = maker.matrixToPuzzle(a);
  solver.solve(root);
  maker.freePuzzle(root);
  return 0;
}
