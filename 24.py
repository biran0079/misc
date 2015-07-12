import math

def add(a, b): return "(%s + %s)" % (a, b)
def sub(a, b): return "(%s - %s)" % (a, b)
def mul(a, b): return "(%s * %s)" % (a, b)
def div(a, b): return "(%s / %s)" % (a, b)

BINARY_OPS = [add, sub, mul, div]

TARGET = 24
EPI = 1e-6

def isSolution(e): 
  try:
    return math.fabs(TARGET - eval(e)) < EPI
  except ZeroDivisionError:
    return False

def partition(l):
  if len(l) == 0:
    yield [], []
  else:
    for a, b in partition(l[1:]):
      yield l[:1] + a, b
      yield a, l[:1] + b

def nonEmptyPartition(l):
  for a, b in partition(l):
    if a and b:
      yield a, b

def expressionGenerator(l):
  if len(l) == 1:
    yield str(float(l[0]))
  else:
    for a,b in nonEmptyPartition(l):
      for op in BINARY_OPS:
        for ea in expressionGenerator(a):
          for eb in expressionGenerator(b):
            yield op(ea, eb)

def solve(l):
  for e in expressionGenerator(l):
    if isSolution(e):
      return e

print solve([3, 7, 2, 1])
print solve([5, 5, 5, 1])
print solve([1, 1, 1, 1])
