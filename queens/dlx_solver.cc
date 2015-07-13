#include "dlx_solver.h"
#include "../dance/exact_cover_puzzle_maker.h"
#include <iostream>

using namespace std;

Node* queenToExactMatch(int n) {
  vector<vector<int> > a(n * n);
  vector<int> secondary(4 * n - 2);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      vector<int>& row = a[i * n + j];
      row.push_back(i);
      row.push_back(n + j);
      row.push_back(2 * n + i + j);
      row.push_back(5 * n - 2 - i + j);
    }
  }
  for (int i = 0; i < 4 * n - 2; i++) {
    secondary[i] = i + 2 * n;
  }
  return ExactCoverPuzzleMaker()
    .sparseMatrixToPuzzleWithSecondaryColumns(a, n * n, 6 * n - 2, secondary);
}

void DLXSolver::solve() {
  Node* puzzle = queenToExactMatch(n);
  DLX dlx(false, &solutionHandler);
  dlx.solve(puzzle);
  cout << solutionHandler.ct << " valid placements for " << n << " queens." << endl;
}
