#include "Board.h"

#define BoardX  20
#define BoardY  15
#define SpotSize  30

void Board::setBoard() {

	al_init();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	

	ALLEGRO_DISPLAY* display = al_create_display(BoardX * SpotSize, BoardY * SpotSize);
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	ALLEGRO_TIMER* timer = al_create_timer(6.0/ 60);
	ALLEGRO_TIMER* frameTimer = al_create_timer(1.0 / 60);
	ALLEGRO_BITMAP* bitmap = al_load_bitmap("node.png");
	ALLEGRO_BITMAP* apple = al_load_bitmap("apple.png");
	ALLEGRO_FONT* font = al_load_ttf_font("Roboto.ttf",48, 0);
	assert(bitmap != NULL);
	assert(font != NULL);
	ALLEGRO_TIMEOUT timeout;
	al_init_timeout(&timeout, 1);

	

	al_install_keyboard();
	//al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_start_timer(timer);
	al_register_event_source(queue, al_get_timer_event_source(frameTimer));
	al_start_timer(frameTimer);
	

	Snake* s = new Snake();
	bool running = true;
	float x = 0;

	srand(time(0));

	Apple* ap = new Apple();

	while (running) {

		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			running = false;

		if (event.type == ALLEGRO_EVENT_TIMER)
			if (event.timer.source == timer) {
				running = updateSnake(s, ap);
				al_clear_to_color(al_map_rgb(240, 240, 240));
				drawSnake(s, bitmap);
				//draw apple
				al_draw_bitmap(apple, (ap->posX - 1) * SpotSize, (ap->posY - 1) * SpotSize, 0);
				al_flip_display();
			}

		ALLEGRO_KEYBOARD_STATE keyState;
		al_get_keyboard_state(&keyState);
		setDirection(s, keyState);
		
		//al_draw_text(font, al_map_rgb(255, 0, 0), x, 0, 0, "Hello World");
		
	}
		

	//afterGame
	al_destroy_display(display);
	al_uninstall_keyboard();
	al_destroy_timer(timer);
	al_destroy_bitmap(bitmap);
}

void Board::drawSnake(Snake* s, ALLEGRO_BITMAP* bitmap) {
	Node* temp = s->head;
	while (temp != nullptr)  {
		al_draw_bitmap(bitmap, (temp->el->posX-1)*SpotSize, (temp->el->posY-1) * SpotSize, 0);
		temp = temp->next;
	}
	delete temp;
}

bool Board::updateSnake(Snake* s, Apple* ap) {
	Node* temp1 = s->tail;
	while (temp1 != s->head) {
		temp1->el->posX = temp1->prev->el->posX;
		temp1->el->posY = temp1->prev->el->posY;
		temp1 = temp1->prev;
	}
	//delete temp1;
	
	switch (s->dir) {
	case RIGHT: s->head->el->posX += 1;
		if (s->head->el->posX == BoardX + 1)
			return false;
		break;
	case UP: s->head->el->posY -= 1;
		if (s->head->el->posY == 0)
			return false;
		break;
	case LEFT: s->head->el->posX -= 1;
		if (s->head->el->posX == 0)
			return false;
		break;
	case DOWN: s->head->el->posY += 1;
		if (s->head->el->posY == BoardY + 1)
			return false;
		break;
	}
	if (s->head->el->posX==ap->posX && s->head->el->posY == ap->posY)

	/*bool apPos = false;
	while !(apPos) {
		apPos = true;
		Node* temp1 = s->tail;
		while (temp1 != s->head) {
			temp1->el->posX = temp1->prev->el->posX;
			temp1->el->posY = temp1->prev->el->posY;
			temp1 = temp1->prev;
		}
	}*/
	return true;
}

void Board::setDirection(Snake* s, ALLEGRO_KEYBOARD_STATE keyState) {
	

	if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT) && s->dir != LEFT)
		s->dir = RIGHT;
	else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT) && s->dir != RIGHT)
		s->dir = LEFT;
	else if (al_key_down(&keyState, ALLEGRO_KEY_UP) && s->dir != DOWN)
		s->dir = UP;
	else if (al_key_down(&keyState, ALLEGRO_KEY_DOWN) && s->dir != UP)
		s->dir = DOWN;
}

/*if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
			if (al_key_down(&keyState, ALLEGRO_KEY_LCTRL))
				x += 10;
			else
				x += 1;
				*/