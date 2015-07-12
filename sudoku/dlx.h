#ifndef __DLX_H__
#define __DLX_H__

#include "sudoku.h"
#include <string>

class DLXSolver : public Sudoku {

public:

  DLXSolver(const std::string& s) : Sudoku(s) {}
  
  virtual void solve();
};

#endif
