#ifndef __SUDOKU_H__
#define __SUDOKU_H__

#include <string>

class Sudoku {

public:
  Sudoku(const std::string& sudoku) : sudoku(sudoku) {}

  virtual void solve() = 0;

  virtual ~Sudoku() {}

protected:
  std::string sudoku;
};

#endif
