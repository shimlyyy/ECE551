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
  int result = f->invoke(mid);
  if (mid == low) {
    return low;
  }
  if (mid == high) {
    return mid - 1;
  }
  if (result == 0) {
    return mid;
  }
  else if (result > 0) {
    /* if (mid == low + 1) {
      return low;
      }*/
    return binarySearchForZero(f, low, mid - 1);
  }
  else {
    /* if (mid == high - 1) {
      return mid;
      }*/
    return binarySearchForZero(f, mid + 1, high);
  }
}
#endif
