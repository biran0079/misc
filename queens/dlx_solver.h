#ifndef __DLX_SOLVER_H__
#define __DLX_SOLVER_H__
#include "queen.h"
#include "../dance/dance.h"
#include <vector>

class DLXSolver : public Queen {

  struct QueenSolutionHandler : public SolutionHandler {

    int ct = 0;

    virtual void handle(const std::vector<int>& unused) {
      ct++;
    }
  };

  QueenSolutionHandler solutionHandler;

public:
  DLXSolver(int n) : Queen(n) {}

  virtual void solve();
};

#endif
