#ifndef __FUNCTION_H__
#define __FUNCTION_H__
template<typename R, typename A>
class Function
{
 public:
  virtual R invoke(A arg) = 0;
  virtual ~Function() {}
};

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (f->invoke(high) < 0) {
    return high - 1;
  }
  if (f->invoke(low) > 0) {
    return low;
  }
  int mid = low + (high - low) / 2;
  if (f->invoke(mid) == 0) {
    return mid;
  }
  else if (f->invoke(mid) > 0) {
    return binarySearchForZero(f, low, mid);
  }
  else {
    return binarySearchForZero(f, mid, low);
  }
}
#endif
