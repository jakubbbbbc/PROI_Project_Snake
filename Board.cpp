#include "Board.h"

#define BoardX  20
#define BoardY  15
#define SpotSize  30

void Board::setBoard() {

	al_init();
	al_init_image_addon();

	ALLEGRO_DISPLAY* display = al_create_display(BoardX * SpotSize, BoardY * SpotSize);
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	ALLEGRO_TIMER* timer = al_create_timer(30.0 / 60);
	ALLEGRO_BITMAP* bitmap = al_load_bitmap("node.png");
	assert(bitmap != NULL);

	

	al_install_keyboard();
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_start_timer(timer);


	Snake* s = new Snake();

	bool running = true;
	float x = 0;
	while (running) {
		al_clear_to_color(al_map_rgb(240, 240, 240));
		//al_draw_text(font, al_map_rgb(255, 0, 0), x+=1, 0, 0, "Hello World");
		drawSnake(s, bitmap);
		updateSnake(s);
		
		ALLEGRO_KEYBOARD_STATE keyState;
		al_get_keyboard_state(&keyState);
		setDirection(s, keyState);
		

		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			running = false;

		

		if (event.type == ALLEGRO_EVENT_TIMER) {
			al_flip_display();
		}
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

void Board::updateSnake(Snake* s) {
	Node* temp1 = s->tail;
	while (temp1 != s->head) {
		temp1->el->posX = temp1->prev->el->posX;
		temp1->el->posY = temp1->prev->el->posY;
		temp1 = temp1->prev;
	}
	//delete temp1;
	
	switch (s->dir) {
	case 1: s->head->el->posX += 1;
		break;
	case 2: s->head->el->posY -= 1;
		break;
	case 3: s->head->el->posX -= 1;
		break;
	case 4: s->head->el->posY += 1;
		break;
	}

}

void setDirection(Snake* s, ALLEGRO_KEYBOARD_STATE keyState) {
	

	if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT) && s->dir != 3)
		s->dir = 1;
	else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT) && s->dir != 1)
		s->dir = 3;
	else if (al_key_down(&keyState, ALLEGRO_KEY_UP) && s->dir != 4)
		s->dir = 2;
	else if (al_key_down(&keyState, ALLEGRO_KEY_DOWN) && s->dir != 2)
		s->dir = 4;
}

