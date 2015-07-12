#include <iostream>
#include <vector>
#include "dance.h"
using namespace std;

namespace {

void cover(Node* col) {
  col->left->right = col->right;
  col->right->left = col->left;
  for (Node* row = col->down; row != col; row = row->down) {
    for (Node* cur = row->right; cur != row; cur = cur->right) {
      cur->up->down = cur->down;
      cur->down->up = cur->up;
      cur->col->size--;
    }
  }
}

void uncover(Node* col) {
  for (Node* row = col->up; row != col; row = row->up) {
    for (Node* cur = row->left; cur != row; cur = cur->left) {
      cur->col->size++;
      cur->down->up = cur;
      cur->up->down = cur;
    }
  }
  col->right->left = col;
  col->left->right = col;
}
} // namespace

bool DLX::solve(Node* root, vector<int>& res) {
  bool found = false;
  if (root->right == root) {
    solutionHandler->handle(res);
    return true;
  }
  Node *selected = root->right;
  for (Node* cur = selected->right; cur != root; cur = cur->right) {
    if (cur->size < selected->size) {
      selected = cur;
    }
  }
  cover(selected);
  for (Node* row = selected->down; row != selected; row = row->down) {
    res.push_back(row->rowIdx);
    for (Node* cur = row->right; cur != row; cur = cur->right) {
      cover(cur->col);
    }
    found |= solve(root, res);
    for (Node* cur = row->left; cur != row; cur = cur->left) {
      uncover(cur->col);
    }
    if (findOneSolution && found) {
      break;
    }
    res.pop_back();
  }
  uncover(selected);
  return found;
}

bool DLX::solve(Node* root) {
  vector<int> res;
  return solve(root, res);
}

void PrintSolution::handle(const vector<int>& solution) {
  for (auto i : solution)
    cout << i << " ";
  cout << endl;
}
