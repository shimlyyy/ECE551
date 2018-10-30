#include <assert.h>

#include <cstdlib>

#include "il.h"
/*void testList(void) {
  IntList a;
  assert(a.head == NULL && a.tail == NULL && a.size == 0);
  a.addFront(3);
  assert(a.size == 1);
  IntList b(a);
  assert(a.head != b.head);

  a.addBack(4);
  assert(a.size == 2);
  a = a;
  b = a;
  assert(a.head != b.head && a.tail != b.tail);
  assert(a[0] == b[0] && a[1] == b[1]);
  IntList e;
  e.addBack(3);
  assert(e.size == 1);
 
IntList f;
f.addFront(3);
f.addFront(4);
f.addBack(5);
f.addBack(7);
assert(f[0] == 4);
assert(f[1] == 3);
assert(f[2] == 5);
assert(f[3] == 7);
f.remove(3);
f.remove(5);
f.remove(6);
f.remove(7);
IntList g;
g.find(2);
// int in1;
// assert(in1 = g[1]);
//int in2;
//  in2 = a[2];

g.addFront(2);
g.remove(2);
assert(g.size == 0);
}*/

void testList(void) {
  IntList a;
  assert(a.head == NULL && a.tail == NULL && a.size == 0);
  a.addFront(3);
  assert(a.size == 1);
  assert(a.getSize() == 1);
  a.addBack(4);
  assert(a.size == 2);
  assert(a.getSize() == 2);
  a.addFront(5);
  assert(a[0] == 5 && a[1] == 3 && a[2] == 4);  //[]
  IntList b;
  b = a;
  assert(b.head != a.head && b.tail != a.tail);
  assert(b.size == a.size);
  IntList c(a);
  assert(b.head != a.head && b.tail != a.tail);
  assert(b.size == a.size);
  a.find(2);
  a.find(3);

  a.remove(2);
  assert(a.size == 3);
  a.remove(3);
  assert(a.size == 2);
  a.remove(4);
  assert(a.size == 1);
  assert(a.tail = a.head);
  a.remove(5);
  assert(a.size == 0);
  assert(a.head == NULL && a.tail == NULL);
  a.remove(2);
  assert(a.size == 0);
}

int main(void) {
  testList();

  return EXIT_SUCCESS;
}
