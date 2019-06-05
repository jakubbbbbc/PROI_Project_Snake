#include "Snake.h"

Snake::Snake() {
	size = 3;
	dir = 0;
	Node* n1 = new Node(7, 6);
	Node* n2 = new Node(6, 6);
	Node* n3 = new Node(5, 6);
	Node* n4 = new Node(4, 6);
	n1->next = n2;
	n2->next = n3;
	n3->next = n4;
	n4->prev = n3;
	n3->prev = n2;
	n2->prev = n1;
	head = n1;
	tail = n4;

}