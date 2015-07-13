#include "search.h"
#include "dlx.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#ifndef SUDOKU_SOLVER
#define SUDOKU_SOLVER Search
#endif

using namespace std;

enum Solver { SEARCH, DLX };

string getSolverName(Solver solver) {
  switch (solver) {
    case SEARCH:
      return "Search";
    case DLX:
      return "DLX";
    default:
      return "unknown";
  }
}

Sudoku* newSolver(Solver solver, const string& s) {
  switch (solver) {
    case SEARCH:
      return new Search(s);
    case DLX:
      return new DLXSolver(s);
    default:
      cerr << "unkonwn solver " << solver << endl;
      exit(-1);
  }
}

vector<string> loadPuzzles(const string& fname) {
  string line;
  ifstream in(fname);
  vector<string> puzzles;
  if (in.is_open()) {
    while (getline(in, line)) {
      puzzles.push_back(line);
    }
    in.close();
  } else {
    cerr << "failed to open file " << fname << endl;
  }
  return puzzles;
}

void solvePuzzleSet(const string& fname, Solver type) {
  vector<string> puzzles = loadPuzzles(fname);
  cout << "Solver: " << getSolverName(type) << endl;
  clock_t st = clock();

  for (auto puzzle : puzzles) {
    Sudoku* solver = newSolver(type, puzzle);
    solver->solve();
    delete solver;
  }

  double durationSec = (clock() - st) * 1.0 / CLOCKS_PER_SEC / puzzles.size();
  cout << "time: " << durationSec << " sec" << endl;
}

int main(int argc, char** args) {
  Solver solver = SEARCH;
  for (int i = 1; i < argc; i++) {
    string a = args[i];
    string prefix = "--solver=";
    if (a.find(prefix) == 0) {
      a = a.substr(prefix.length());
      if (a == "dlx") {
        solver = DLX;
      }
    }
  }
  solvePuzzleSet("hard.txt", solver);
  solvePuzzleSet("hardest.txt", solver);
  return 0;
}
