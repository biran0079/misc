#ifndef __DANCE_H__
#define __DANCE_H__
#include "node.h"
#include <vector>

struct SolutionHandler {
  virtual void handle(const std::vector<int>& solution) = 0;
};

struct PrintSolution : SolutionHandler {

  virtual void handle(const std::vector<int>& solution);
};

struct DLX {

  DLX(bool findOneSolution, SolutionHandler* solutionHandler) :
    findOneSolution(findOneSolution),
    solutionHandler(solutionHandler) {}

  bool solve(Node* root);

private:

  bool findOneSolution;
  SolutionHandler* solutionHandler;

  bool solve(Node* root, std::vector<int>& res);
};

#endif
