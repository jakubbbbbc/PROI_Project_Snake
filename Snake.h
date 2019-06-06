#ifndef SNAKE_H
#define SNAKE_H

#include<iostream>
#include "Node.h"


class Snake {
public:
	int size;
	int dir;
	Node* head;
	Node* tail;
public:
	Snake();
	void addSegment(int x, int y);
};

#endif

