#include <iostream>
#include <time.h>
#include "search.h"
using namespace std;

int numOfOnes(int t) {
  int res = 0;
  while (t) {
    t &= t-1;
    res++;
  }
  return res;
}


void Search::print() {
  for (int i = 0; i < 81; i++) {
    for (int j = 0; j < 9; j++) {
      if (a[i] == (1 << j)) {
        cout << (1 + j) << " ";
        break;
      }
    }
    if (i % 9 == 8) cout << endl;
  }
}

bool Search::search() {
  int minV = 0xffffff, minI = -1;
  for (int i = 0; i < 81; i++) {
    if (a[i] == 0) {
      int t = numOfOnes(row[R[i]] & col[C[i]] & block[B[i]]);
      if (t == 0) return false;
      if (t < minV) {
        minV = t;
        minI = i;
      }
    }
  }
  if (minI == -1) return true;
  int i = minI;
  int t = row[R[i]] & col[C[i]] & block[B[i]];
  while (t) {
    int t2 = t & (t-1), x = t - t2;
    t = t2;
    row[R[i]] &= ~x;
    col[C[i]] &= ~x;
    block[B[i]] &= ~x;
    a[i] = x;
    if (search()) return true;
    row[R[i]] |= x;
    col[C[i]] |= x;
    block[B[i]] |= x;
    a[i] = 0;
  }
  return false;
}

void Search::init() {
  if (initialized) return;
  for (int i = 0; i < 81; i++) {
    R[i] = i / 9;
    C[i] = i % 9;
    B[i] = R[i] / 3 * 3 + C[i] / 3;
  }
  initialized = true;
}

Search::Search(const string& s) : Sudoku(s) {
  init();
  for (int i = 0; i < 9; i++) {
    block[i] = row[i] = col[i] = (1 << 9) - 1;
  }
  for (int i = 0; i < 81; i++) {
    if (s[i] >= '1' && s[i] <= '9') {
      a[i] = 1 << (s[i] - '1');
      int ri = i / 9, ci = i % 9, bi = ri / 3 * 3 + ci / 3;
      row[ri] &= ~a[i];
      col[ci] &= ~a[i];
      block[bi] &= ~a[i];
    } else {
      a[i] = 0;
    }
  }
}

void Search::solve() {
  if (search()) 
    print();
  else
    cout << "no solution" << endl;
}

bool Search::initialized = false;
int Search::R[] = {0};
int Search::C[] = {0};
int Search::B[] = {0};

