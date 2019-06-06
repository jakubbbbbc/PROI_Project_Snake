#ifndef BOARD_H
#define BOARD_H

#include "Snake.h"
#include "Apple.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <ctime>

class Board {
public:
	enum Direction { RIGHT, UP, LEFT, DOWN };
	void game();
	void drawSnake(Snake* s, ALLEGRO_BITMAP* bitmap);
	bool updateSnake(Snake* s, Apple* ap, bool hasEaten);
	void setDirection(Snake* s, ALLEGRO_KEYBOARD_STATE keyState);
	bool updateApple(Snake*, Apple**);
};

#endif
