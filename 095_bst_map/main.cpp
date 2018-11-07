#include <assert.h>

#include "bstmap.h"
#include "map.h"
int main(void) {
  BstMap<int, int> k = BstMap<int, int>();
  k.add(3, 4);
  assert(k.lookup(3) == 4);
  k.add(5, 5);
  k.add(7, 2);
  k.remove(7);
  k.add(7, 3);
  assert(k.lookup(7) == 3);
}
