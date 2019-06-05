#ifndef NODE_H
#define NODE_H

#include "Body.h"

class Node {
public:
	Body* el;
	Node* next;
	Node* prev;

	//methods
	Node(int x, int y) {
		el = new Body(x,y);
		next = nullptr;
	}
};


#endif