#ifndef __BITWISE_SOLVER__
#define __BITWISE_SOLVER__

#include "queen.h"

class BitWiseSolver : public Queen {

public:
  BitWiseSolver(int n) : Queen(n), ulimit((1 << n) - 1), ct(0) {}

  virtual void solve();

private:
  int ulimit;
  int ct;
  void search(int row, int ld, int rd);
};
#endif
