//==============================================//
// GameLogicTest                                //
//                                              //
// Content: Animation class                     //
// File:    Animation.cpp                       //
//                                              //
// Copyright (c) 2014, Max Giller               //
//==============================================//

#include "Animation.h"

namespace GameLogicTest
{
	Animation::Animation(ALLEGRO_BITMAP* spritesheet, int tilesX, int tilesY)
	{
		Initialize(spritesheet, tilesX, tilesY, 0, (tilesX * tilesY) - 1);
	}

	Animation::Animation(ALLEGRO_BITMAP* spritesheet, int tilesX, int tilesY, int firstTile, int lastTile)
	{
		Initialize(spritesheet, tilesX, tilesY, firstTile, lastTile);
	}

	Animation::~Animation()
	{
		al_destroy_bitmap(spritesheet);
		this->frames.clear();
	}

	void Animation::Initialize(ALLEGRO_BITMAP* spritesheet, int tilesX, int tilesY, int firstTile, int lastTile)
	{
		this->spritesheet = spritesheet;
		this->totalWidth = al_get_bitmap_width(spritesheet);
		this->totalHeight = al_get_bitmap_height(spritesheet);
		this->fps = 7;
		this->tileWidth = this->totalWidth / tilesX;
		this->tileHeight = this->totalHeight / tilesY;

		for (int i = firstTile; i <= lastTile; ++i)
		{
			this->frames.push_back(AnimationFrame{ (i % tilesX) * this->tileWidth, (i / tilesX) * this->tileHeight, this->tileWidth, this->tileHeight });
		}
		this->totalFrames = this->frames.size();
		this->index = 0;
		this->time = 0;
	}

	void Animation::Start()
	{
		if(!this->isRunning) this->isRunning = true;
	}

	void Animation::Stop()
	{
		if(this->isRunning) this->isRunning = false;
	}

	void Animation::Reset()
	{
		this->index = 0;
	}

	void Animation::Update(float deltaTime)
	{
		if (this->isRunning)
		{
			this->time += deltaTime;
			if (time > 1.0f / this->fps)
			{
				this->index = (this->index + 1) % this->totalFrames;
				time -= 1.0f / this->fps;
			}
		}
	}

	void Animation::Draw(int x, int y)
	{
		al_draw_bitmap_region(this->spritesheet, this->frames[this->index].x, 
												 this->frames[this->index].y, 
												 this->frames[this->index].width, 
												 this->frames[this->index].height,
												 x - this->frames[this->index].width / 2,
												 y - this->frames[this->index].height / 2,
												 NULL);
	}

	bool Animation::IsRunning()
	{
		return this->isRunning;
	}
}