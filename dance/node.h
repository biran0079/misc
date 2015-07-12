#ifndef __NODE_H__
#define __NODE_H__

struct Node {
  Node *up, *down, *left, *right, *col;
  int size, rowIdx;
};

#endif
