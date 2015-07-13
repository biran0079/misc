#ifndef __EXACT_COVER_PUZZLE_MAKER_H__
#define __EXACT_COVER_PUZZLE_MAKER_H__

#include "node.h"
#include <vector>

struct ExactCoverPuzzleMaker {

  // Input is a list of fixed sized list of 0 and 1.
  Node* matrixToPuzzle(const std::vector<std::vector<int> >& a);

  // Input is a list of lists. 
  // Each inner list stores sorted column indices of each entry with value 1 in the row.
  Node* sparseMatrixToPuzzle(const std::vector<std::vector<int> >& a, int rN, int cN);

  // Secondary columns does not need to be covered in a solution, but solution sets should be
  // disjoint on all columns, including secondary ones.
  Node* sparseMatrixToPuzzleWithSecondaryColumns(
      const std::vector<std::vector<int> >& a, int rN, int cN, const std::vector<int>& secondaryCols);

  void freePuzzle(Node* root);
};

#endif
