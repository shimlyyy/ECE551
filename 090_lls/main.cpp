#include <assert.h>

#include <cstdlib>

#include "ll.h"

void testList(void) {
  LinkedList<int> a;
  assert(a.head == NULL && a.tail == NULL && a.size == 0);
  a.addFront(3);
  assert(a.size == 1);
  assert(a.getSize() == 1);
  a.addBack(4);
  assert(a.size == 2);
  assert(a.getSize() == 2);
  a.addFront(5);
  assert(a[0] == 5 && a[1] == 3 && a[2] == 4);  //[]
  LinkedList<int> b;
  b = a;
  assert(b.head != a.head && b.tail != a.tail);  //shallow copy
  assert(b.size == a.size);                      //check size
  /*  LinkedList<int> c(a);
  assert(b.head != a.head && b.tail != a.tail);
  assert(b.size == a.size);
  assert(a.find(2) == -1);*/
  //more clear test case
  a.addBack(6);
  a.remove(3);  //remove middle
//  assert(a.find(3) == -1);
 // assert(a.find(6) == 2);
  assert(a.size == 3);                    //check size
  assert(a.head->next->data == 4);        //check front's next
  assert(a.head->next->prev->data == 5);  //check next's prev
  a.remove(5);                            //remove first item
  assert(a.head->data == 4);              //check head
  a.remove(6);                            //remove final item
  assert(a.tail->data == 4);              //check tail

  //can pass all tests but less clear
  /* a.remove(3);                                                                                                                                                                                           
  assert(a.size == 2);                                                                                                                                                                                      
  a.remove(4);                                                                                                                                                                                              
  a.remove(5);                                                                                                                                                                                              
  assert(a.head == NULL && a.tail == NULL);*/
}

int main(void) {
  testList();

  return EXIT_SUCCESS;
}
