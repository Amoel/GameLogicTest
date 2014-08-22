//==============================================//
// GameLogicTest                                //
//                                              //
// Content: Main                                //
// File:    Main.cpp                            //
//                                              //
// Copyright (c) 2014, Max Giller               //
//==============================================//

#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_image.h>

#include "Level.h"

#define ScreenWidth     1280
#define ScreenHeight    800
#define WindowTitle     "GameLogicTest by Max Giller"

#define COLOR_BLACK     al_map_rgb(0, 0, 0)
#define COLOR_WHITE     al_map_rgb(255, 255, 255)

const float FPS = 60;


ALLEGRO_DISPLAY* display;
GameLogicTest::Level* level;

int main()
{
	double time = 0;
	bool run = true;

	if (!al_init())
	{
		/* Show a window with an error message if the initialization of Allegro failed. */
		al_show_native_message_box(NULL, NULL, NULL, "Could not initialize Allegro 5", NULL, NULL);
	}

	al_init_image_addon();
	/* Create the display with the defined title, width and height. */
	display = al_create_display(ScreenWidth, ScreenHeight);
	

	if (!display)
	{
		/* Show a window with an error message if the initialization of the display failed. */
		al_show_native_message_box(NULL, NULL, NULL, "Could not create Allegro window", NULL, NULL);
	}
	
	al_set_window_title(display, WindowTitle);
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_mouse();

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);

	ALLEGRO_EVENT_QUEUE* eventQueue = al_create_event_queue();
	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_timer_event_source(timer));
	al_register_event_source(eventQueue, al_get_mouse_event_source());
	level = new GameLogicTest::Level();

	al_start_timer(timer);

	/* main gameloop */
	while (run)
	{
		ALLEGRO_EVENT events;
		al_wait_for_event(eventQueue, &events);
		
		if (events.type == ALLEGRO_EVENT_TIMER)
		{
			float deltaTime = (float)(al_get_time() - time);
			time = al_get_time();
			level->Update(deltaTime);
			level->Draw();

			al_flip_display();
			al_clear_to_color(COLOR_BLACK);
		}
		else if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (events.mouse.button & 1)
				level->MovePlayer(events.mouse.x, events.mouse.y);
		}
		else if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			run = false;
		}

		
	}
	delete(level);
	al_stop_timer(timer);
	al_destroy_timer(timer);
	al_destroy_display(display);
	return 0;
}