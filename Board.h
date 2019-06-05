#ifndef BOARD_H
#define BOARD_H

#include "Snake.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

class Board {
public:
	void setBoard();
	void drawSnake(Snake* s, ALLEGRO_BITMAP* bitmap);
	void updateSnake(Snake* s);
	void setDirection(Snake* s, ALLEGRO_KEYBOARD_STATE keyState);
};

#endif