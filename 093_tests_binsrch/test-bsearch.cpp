#include <math.h>
#include <stdio.h>

#include <cstdlib>

#include "function.h"
int binarySearchForZero(Function<int, int> * f, int low, int high);
class linearFunction : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return 2 * arg + 10; }
};
class CountedIntFn : public Function<int, int>
{
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};
void check(Function<int, int> * f, int low, int high, int expected_ans, const char * mesg) {
  int ans = binarySearchForZero(f, low, high);
  if (ans == expected_ans) {
    printf("function %s between %d and %d success\n", mesg, low, high);
  }
  else {
    printf("fucntion %s between %d and %d :answer is not equal to expected ans\n", mesg, low, high);
    exit(EXIT_FAILURE);
  }
}

class powerFunction : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return arg * (arg - 2); }
};

int main(void) {
  Function<int, int> * f2 = new linearFunction;
  const char * mesg2 = "2*arg+10";
  Function<int, int> * c = new CountedIntFn(8, f2, mesg2);
  check(c, -138, -10, -11, mesg2);

  Function<int, int> * f3 = new powerFunction;
  const char * mesg3 = "arg*(arg-2)";
  Function<int, int> * d = new CountedIntFn(8, f3, mesg3);
  check(d, 0, 128, 2, mesg3);
  Function<int, int> * d1 = new CountedIntFn(8, f3, mesg3);
  check(d1, 2, 130, 2, mesg3);

  return EXIT_SUCCESS;
}
