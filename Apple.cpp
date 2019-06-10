#include "Apple.h"


Apple::Apple() {
	srand(time(0));
	posX = rand() % 20 + 1;
	posY = rand() % 15+1;
}

Apple::Apple(int x, int y) {
	posX = x;
	posY = y;A
}