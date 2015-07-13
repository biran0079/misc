#ifndef __QUEEN_H__
#define __QUEEN_H__

class Queen {

public:
  
  Queen(int n) : n(n) {}

  virtual void solve() = 0;

protected:
  int n;
};

#endif
