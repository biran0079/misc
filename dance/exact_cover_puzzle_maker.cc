#include <vector>
#include "exact_cover_puzzle_maker.h"

using namespace std;

Node* ExactCoverPuzzleMaker::sparseMatrixToPuzzle(const vector<vector<int> >& a, int rN, int cN) {
  int nodeN = cN + 1;
  for (int i = 0; i < rN; i++)
    nodeN += a[i].size();
  Node* nodes = new Node[nodeN];
  Node** cols = new Node*[cN];
  int next = 0;
  Node* root = &nodes[next++];
  root->left = root;
  root->right = root;
  for (int i = 0; i < cN; i++) {
    Node* cur = &nodes[next++];
    cols[i] = cur;
    cur->size =0;
    cur->col = cur;

    cur->left = root->left;
    root->left->right = cur;
    cur->right = root;
    root->left = cur;

    cur->up = cur;
    cur->down = cur;
  }

  for (int i = 0;  i < rN; i++) {
    Node* p = 0;
    for (int colIdx : a[i]) {
      Node *col = cols[colIdx];
      Node* cur = &nodes[next++];
      cur->rowIdx = i;
      cur->col = col;
      if (p) {
        cur->left = p;
        cur->right = p->right;
        cur->right->left = cur;
        cur->left->right = cur;
      } else {
        cur->left = cur->right = cur;
      }
      cur->up = col->up;
      cur->down = col;
      cur->up->down = cur;
      cur->down->up = cur;
      p = cur;
      col->size++;
    }
  }
  delete[] cols;
  return root;
}

Node* ExactCoverPuzzleMaker::matrixToPuzzle(const vector<vector<int> >& a) {
  int rN = a.size(), cN = a[0].size();
  vector<vector<int> > sa(a.size());
  for (int i = 0; i < rN; i++) {
    for (int j = 0; j < cN; j++) {
      if (a[i][j]) {
        sa[i].push_back(j);
      }
    }
  }
  return sparseMatrixToPuzzle(sa, rN, cN);
}

void ExactCoverPuzzleMaker::freePuzzle(Node* root) {
  delete[] root;
}
