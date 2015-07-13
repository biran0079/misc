#include "bitwise_solver.h"
#include <iostream>

using namespace std;

void BitWiseSolver::solve() {
  search(0, 0, 0);
  cout << ct << " valid placements for " << n << " queens." << endl;
}

void BitWiseSolver::search(int row, int ld, int rd) {
  if (row == ulimit) {
    ct++;
    return;
  }
  int t = ulimit & ~(ld | rd | row);
  while (t) {
    int k = t & -t;
    search(row + k, (ld + k) << 1, (rd + k) >> 1);
    t -= k;
  }
}
