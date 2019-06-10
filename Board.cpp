#include "Board.h"

#define BoardX  20
#define BoardY  15
#define SpotSize  30

void Board::game(){
	al_init();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	

	ALLEGRO_DISPLAY* display = al_create_display(BoardX * SpotSize, BoardY * SpotSize+20);
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	ALLEGRO_TIMER* timer = al_create_timer(6.0/ 60);
	ALLEGRO_TIMER* frameTimer = al_create_timer(1.0 / 60);
	ALLEGRO_BITMAP* bitmap = al_load_bitmap("node.png");
	ALLEGRO_BITMAP* apple = al_load_bitmap("apple.png");
	ALLEGRO_FONT* font = al_load_ttf_font("Roboto.ttf", 16, 0);
	ALLEGRO_FONT* font1 = al_load_ttf_font("Roboto.ttf", 48, 0);
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
	
	Snake* s=nullptr;
	int score = 0;
	int highScore = 0;
	bool done = false;
	
	//game loop
	while (!done) {
		bool running = true;
		//menu
		bool menu = true;
		while (menu) {
			ALLEGRO_EVENT event1;
			al_wait_for_event(queue, &event1);
			if (event1.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				running = false;
				done = true;
				menu = false;
			}
			al_clear_to_color(al_map_rgb(240, 240, 240));
			al_draw_textf(font1, al_map_rgb(0, 0, 0), BoardX * SpotSize*0.1+50, BoardY * SpotSize*0.3, 0, "Your highscore: %i", highScore);
			al_draw_text(font1, al_map_rgb(0, 0, 0), BoardX * SpotSize*0.2+10, BoardY * SpotSize*0.6, 0, "Press M to play");
			al_flip_display();
			ALLEGRO_KEYBOARD_STATE keyState1;
			al_get_keyboard_state(&keyState1);
			if (al_key_down(&keyState1, ALLEGRO_KEY_M))
				menu = false;
		}
		
		s = new Snake();
		bool paused = false;
		srand(time(0));

		Apple* ap = new Apple();

		while (running) {

			ALLEGRO_EVENT event;
			al_wait_for_event(queue, &event);
			if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				running = false;
				done = true;
			}
			if (paused)
				al_draw_text(font1, al_map_rgb(255, 0, 0), BoardX * SpotSize*0.3, BoardY * SpotSize*0.4, 0, "Paused");

			if (event.type == ALLEGRO_EVENT_TIMER && !paused)
				if (event.timer.source == timer) {
					try {
						if (updateApple(s, &ap))
							running = updateSnake(s, ap, true);//gets bigger
						else
							running = updateSnake(s, ap, false);//size the same
					}
					catch (std::string w)
					{
						std::cout << "Wyjatek: " << w;
					}

					al_clear_to_color(al_map_rgb(240, 240, 240));

					//draw apple
					al_draw_bitmap(apple, (ap->posX - 1) * SpotSize, (ap->posY - 1) * SpotSize, 0);
					
					//draw snake
					if (running)
					try
					{
						drawSnake(s, bitmap);
					}
					catch (std::string w)
					{
						std::cout << "Wyjatek: " << w;
					}
						

					//draw frame
					al_draw_line(0, 0, 0, BoardY * SpotSize, al_map_rgb(0, 0, 0), 5); //left
					al_draw_line(0, 0, BoardX * SpotSize, 0, al_map_rgb(0, 0, 0), 5); //top
					al_draw_line(0, BoardY * SpotSize, BoardX * SpotSize, BoardY * SpotSize, al_map_rgb(0, 0, 0), 3); //bottom
					al_draw_line(BoardX * SpotSize, 0, BoardX * SpotSize, BoardY * SpotSize, al_map_rgb(0, 0, 0), 3); //right

					//draw score
					score = s->size;
					if (score > highScore)
						highScore = score;
					al_draw_textf(font, al_map_rgb(0, 0, 0), 0, BoardY * SpotSize, 0, "score: %i", score);
					al_draw_textf(font, al_map_rgb(0, 0, 0), BoardX * SpotSize/2, BoardY * SpotSize, 0, "high score: %i", highScore);

				}

			al_flip_display();

			ALLEGRO_KEYBOARD_STATE keyState;
			al_get_keyboard_state(&keyState);
			if (al_key_down(&keyState, ALLEGRO_KEY_P))
				paused = true;
			else if (al_key_down(&keyState, ALLEGRO_KEY_L))
				paused = false;
			if (!paused)
				setDirection(s, keyState);

		}
	}
		

	//afterGame
	al_destroy_display(display);
	al_uninstall_keyboard();
	al_destroy_timer(timer);
	al_destroy_bitmap(bitmap);
	al_destroy_font(font);
}

void Board::drawSnake(Snake* s, ALLEGRO_BITMAP* bitmap) {
	if (s == nullptr) {
		std::string exception = "snake not existing, cannot draw snake!";
		throw exception;
	}
	Node* temp = s->head;

	while (temp != nullptr)  {
		al_draw_bitmap(bitmap, (temp->el->posX-1)*SpotSize, (temp->el->posY-1) * SpotSize, 0);
		temp = temp->next;
	}
	delete temp;
}

bool Board::updateSnake(Snake* s, bool hasEaten) {
	Node* temp1 = s->tail;
	if (hasEaten) {
		s->addSegment(s->tail->el->posX, s->tail->el->posY);
	}
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
	temp1 = s->tail;
	while (temp1 != s->head) {
		if (temp1->el->posX == s->head->el->posX && temp1->el->posY == s->head->el->posY)
			return false;
		temp1 = temp1->prev;
	}
	//delete temp1;
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

bool Board::updateApple(Snake* s, Apple** ap) {
	if (s == nullptr) {
		std::string exception = "snake not existing, cannot update Apple!";
		throw exception;
	}
	if (s->head->el->posX == (*ap)->posX && s->head->el->posY == (*ap)->posY) {
		std::cout << "apple eaten\n";
		int x, y;
		bool apOk;
		Node* temp = s->head;
		do {
			apOk = true;
			x = rand() % 20 + 1;
			y = rand() % 15 + 1;
			//int i = 1;
			temp = s->head;
			while (temp != nullptr) {
				//std::cout << i << std::endl;
				//i++;
				if (temp->el->posX == x && temp->el->posY == y) {
					/*
					wyj¹tek ¿e temp=null
					*/
					apOk = false;
					//break;
				}
				temp = temp->next;
			}
			delete temp;
		} while (!apOk);
		//(*ap) = new Apple(s->tail->prev->el->posX, s->tail->prev->el->posY);
		(*ap) = new Apple(x, y);
		return true;
	}
	return false;
}
