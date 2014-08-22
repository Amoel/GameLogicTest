//==============================================//
// GameLogicTest                                //
//                                              //
// Content: Level class                         //
// File:    Level.cpp                           //
//                                              //
// Copyright (c) 2014, Max Giller               //
//==============================================//

#pragma once

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_font.h>
#include "Player.h"
#include "Enemy.h"
#include "Tile.h"
#include "AStarNode.h"
#include "AStarPathfinder.h"

#define LevelWidth   32
#define LevelHeight  18
#define TileSize     64

namespace GameLogicTest
{
	/* Level contains the basic structure of the map, the player and the enemies. */
	class Level
	{
	private:
		ALLEGRO_BITMAP*      tileset;
		ALLEGRO_BITMAP*      vignette;
		ALLEGRO_FONT*        font;
		Tile                 tiles[LevelWidth][LevelHeight];
		FPoint2D             levelOffset;

		Player*              player;
		std::vector<Enemy*>  enemies;
		AStarPathfinder*     pathfinder;

	public:
		Level();
		~Level();

		/* Moves the player to a specific coordinate on the map depending on where the mouse was clicked. */
		void MovePlayer(int cursorX, int cursorY);
		void Update(float deltaTime);
		void Draw();
	};
}