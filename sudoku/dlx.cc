#include "sudoku.h"
#include "dlx.h"
#include "../dance/dance.h"
#include "../dance/exact_cover_puzzle_maker.h"
#include <map>
#include <vector>
#include <iostream>
using namespace std;

namespace {

struct SudokuSolutionPrinter : SolutionHandler {
  
  string sudoku;

  SudokuSolutionPrinter(const string& sudoku) : sudoku(sudoku) {}

  virtual void handle(const vector<int>& solution) {
    string res = sudoku;
    for (int idx : solution) {
      int i = idx / 9;
      int k = idx % 9;
      res[i] = '1' + k;
    }
    for (int i = 0; i < 81; i++) {
      cout << res[i] << " ";
      if (i % 9 == 8) cout << endl;
    }
  }
};

int getIdx(map<int, int>& m, int i) {
  if (m.find(i) != m.end()) return m[i];
  int res = m.size();
  return m[i] = res;
}

Node* sudokuToExactCoverPuzzle(const string& s) {
  int block[9], row[9], col[9];
  for (int i = 0; i < 9; i++) {
    block[i] = row[i] = col[i] = (1 << 9) - 1;
  }
  for (int i = 0; i < 81; i++) {
    if (s[i] >= '1' && s[i] <= '9') {
      int t = ~(1 << (s[i] - '1'));
      int ri = i / 9, ci = i % 9, bi = ri / 3 * 3 + ci / 3;
      row[ri] &= t;
      col[ci] &= t;
      block[bi] &= t;
    }
  }
  map<int, int> colIdx;
  vector<vector<int> > sa(81 * 9);
  for (int i = 0; i < 81; i++) {
    if (s[i] >= '1' && s[i] <= '9') continue;
    int ri = i / 9, ci = i % 9, bi = ri / 3 * 3 + ci / 3;
    for (int j = 0; j < 9; j++) {
      if (block[bi] & row[ri] & col[ci] & (1 << j)) {
        vector<int> &row = sa[i * 9 + j];
        row.push_back(getIdx(colIdx, ri * 9 + j));
        row.push_back(getIdx(colIdx, 81 + ci * 9 + j));
        row.push_back(getIdx(colIdx, 81 * 2 + bi * 9 + j));
        row.push_back(getIdx(colIdx, 81 * 3 + i));
      }
    }
  }
  return ExactCoverPuzzleMaker().sparseMatrixToPuzzle(sa, 81 * 9, colIdx.size());
}
} // namespace

void DLXSolver::solve() {
  Node* puzzle = sudokuToExactCoverPuzzle(sudoku);
  SudokuSolutionPrinter handler(sudoku);
  DLX dlx(true, &handler);
  dlx.solve(puzzle);
}
