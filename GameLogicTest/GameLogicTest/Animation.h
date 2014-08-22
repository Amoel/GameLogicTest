//==============================================//
// GameLogicTest                                //
//                                              //
// Content: Animation class                     //
// File:    Animation.h                         //
//                                              //
// Copyright (c) 2014, Max Giller               //
//==============================================//

#pragma once

#include <vector>
#include <cmath>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include "AnimationFrame.h"

namespace GameLogicTest
{
	/* Basic animation class. Uses spritesheet segments. */
	class Animation
	{
	private:
		ALLEGRO_BITMAP* spritesheet;
		std::vector<AnimationFrame> frames;
		int totalFrames;
		int fps;
		float time;
		int index;
		bool isRunning;

		int totalWidth, totalHeight, tileWidth, tileHeight;

		void Initialize(ALLEGRO_BITMAP* spritesheet, int tilesX, int tilesY, int firstTile, int lastTile);

	public:
		/* Constructor for when all images in the spritesheet should be used for the animation. */
		Animation(ALLEGRO_BITMAP* spritesheet, int tilesX, int tilesY);
		/* Constructor for when a specific range of images in the spritesheet should be used for the animation. */
		Animation(ALLEGRO_BITMAP* spritesheet, int tilesX, int tilesY, int firstTile, int lastTile);
		~Animation();
		
		/* Starts the animation. */
		void Start();
		/* Stopps the animation. */
		void Stop();
		/* Resets the animation to the first frame. */
		void Reset();
		void Update(float deltaTime);
		void Draw(int x, int y);

		/* Returns whether the animation is running or has been stopped. */
		bool IsRunning();
	};
}