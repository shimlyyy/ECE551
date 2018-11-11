#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t pq;
  for (uint64_t i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      pq.push(new Node(i, counts[i]));
    }
  }
  while (pq.size() > 1) {
    Node * l = pq.top();
    pq.pop();
    Node * r = pq.top();
    pq.pop();
    Node * sum = new Node(l, r);
    pq.push(sum);
  }
  return pq.top();
}
