//==============================================//
// GameLogicTest                                //
//                                              //
// Content: Entity class                        //
// File:    Entity.h                            //
//                                              //
// Copyright (c) 2014, Max Giller               //
//==============================================//

#pragma once

#include <queue>
#include <map>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include "Animation.h"
#include "Point.h"

namespace GameLogicTest
{
	enum CharacterFaceDirection { UP, DOWN, LEFT, RIGHT };

	/* Base class for the player and all enemies. */
	class Entity
	{
	private:

	protected:
		ALLEGRO_BITMAP* Spritesheet;
		/* Current animation, depending on the direction the entity is looking at. */
		Animation* CurrentAnimation;
		/* Map of four possible animations, one for every direction on the field. */
		std::map<CharacterFaceDirection, Animation*> Animations;

	public:
		/* Absolute location of the entity in the level. */
		FPoint2D Location;
		/* Coordinates of the entitiy on the grid. */
		Point2D GridLocation;
		/* Queue of the coordinates by which the entity travels. */
		std::queue<Point2D> WalkingQueue;

		virtual void Update(float deltaTime) = 0;
		virtual void Draw(FPoint2D levelOffset) = 0;
	};
}