#ifndef __SEARCH_H__
#define __SEARCH_H__
#include "sudoku.h"
#include <string>

class Search : public Sudoku {

  int block[9], row[9], col[9];
  int a[81];

  static int R[81], C[81], B[81];
  static bool initialized;

  void print();
  bool search();
  void init();

public:

  Search(const std::string& s);
  
  virtual void solve();
};

#endif
