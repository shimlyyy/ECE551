
#include <iostream>

#include "bstset.h"
#include "set.h"
int main(void) {
  BstSet<int> k;
  k.add(3);
  k.add(5);
  k.add(7);
  k.remove(7);
  k.add(3);
  k.add(7);
  k.printtest();
}
