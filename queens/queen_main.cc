#include "bitwise_solver.h"
#include "dlx_solver.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

enum SolverType { BITWISE, DLX };

string getSolverName(SolverType solver) {
  switch (solver) {
    case BITWISE:
      return "bit_wise";
    case DLX:
      return "DLX";
    default:
      return "unknown";
  }
}

Queen* newSolver(SolverType solver, int n) {
  switch (solver) {
    case BITWISE:
      return new BitWiseSolver(n);
    case DLX:
      return new DLXSolver(n);
    default:
      cerr << "unkonwn solver " << solver << endl;
      exit(-1);
  }
}


int main(int argc, char** args) {
  SolverType type = BITWISE;
  for (int i = 1; i < argc; i++) {
    string a = args[i];
    string prefix = "--solver=";
    if (a.find(prefix) == 0) {
      a = a.substr(prefix.length());
      if (a == "dlx") {
        type = DLX;
      }
    }
  }

  clock_t st = clock();

  Queen* solver = newSolver(type, 14);
  solver->solve();
  delete solver;

  double durationSec = (clock() - st) * 1.0 / CLOCKS_PER_SEC;
  cout << "time: " << durationSec << " sec" << endl;
  return 0;
}
