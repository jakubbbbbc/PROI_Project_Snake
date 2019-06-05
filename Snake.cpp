#include "Snake.h"

Snake::Snake() {
	size = 1;
	dir = 1;
	Node* n1 = new Node(7, 6);
	Node* n2 = new Node(6, 6);
	Node* n3 = new Node(5, 6);
	n1->next = n2;
	n2->next = n3;
	n3->prev = n2;
	n2->prev = n1;
	head = n1;
	tail = n3;

}