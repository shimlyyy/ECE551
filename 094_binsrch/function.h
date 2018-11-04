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
  int mid = low + (high - low) / 2;
  if (high - low <= 1) {
    return high - 1;
  }
  int result = f->invoke(mid);
  if (result == 0) {
    return mid;
  }
  else if (result > 0) {
    return binarySearchForZero(f, low, mid);
  }
  else {
    return binarySearchForZero(f, mid + 1, high);
  }
}
#endif
