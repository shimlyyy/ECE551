#include <assert.h>

#include <iostream>

#include "bstmap.h"
#include "map.h"
int main(void) {
  BstMap<int, int> k = BstMap<int, int>();
  k.add(3, 4);
  std::cout << k.lookup(3) << '\n';
  k.add(5, 5);
  k.add(7, 2);
  k.remove(7);
  k.add(7, 3);
  k.printtest();
}
