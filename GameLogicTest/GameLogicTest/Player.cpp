//==============================================//
// GameLogicTest                                //
//                                              //
// Content: Player class                        //
// File:    Player.cpp                          //
//                                              //
// Copyright (c) 2014, Max Giller               //
//==============================================//

#include "Player.h"

namespace GameLogicTest
{
	Player::Player(int life)
	{
		Spritesheet = al_load_bitmap("Graphics/gfx_playerSpritesheet.png");

		Animations = std::map<CharacterFaceDirection, Animation*>();

		/* Creates four Animations, each with a section of Spritesheet for the four direction the player can look at. */
		this->Animations.insert(std::pair<CharacterFaceDirection, Animation*>(UP, new Animation(Spritesheet, 3, 4, 9, 11)));
		this->Animations.insert(std::pair<CharacterFaceDirection, Animation*>(DOWN, new Animation(Spritesheet, 3, 4, 0, 2)));
		this->Animations.insert(std::pair<CharacterFaceDirection, Animation*>(LEFT, new Animation(Spritesheet, 3, 4, 3, 5)));
		this->Animations.insert(std::pair<CharacterFaceDirection, Animation*>(RIGHT, new Animation(Spritesheet, 3, 4, 6, 8)));
		
		/* Let the current animation point to the UP animation, so the player looks down when the game starts. */
		CurrentAnimation = Animations.find(UP)->second;
		CurrentAnimation->Start();

		this->GridLocation = Point2D{ 1, 1 };
		this->Location = FPoint2D{ 96, 96 };

		this->WalkingQueue = std::queue<Point2D>();
	}

	Player::~Player()
	{
		this->Animations.clear();
		delete(this->CurrentAnimation);
	}

	/* Changes the animation depending on a new direction. */
	void Player::ChangeDirection(CharacterFaceDirection newDirection)
	{
		if (this->CurrentAnimation == this->Animations.find(newDirection)->second) return;
		this->CurrentAnimation->Stop();
		this->CurrentAnimation->Reset();
		this->CurrentAnimation = this->Animations[newDirection];
		this->CurrentAnimation->Start();
	}

	void Player::MoveToTile(int x, int y)
	{
		GridLocation = Point2D{ x, y };
	}

	void Player::Update(float deltaTime)
	{
		if (std::sqrt(std::pow(this->Location.X - (this->GridLocation.X * 64 + 32), 2.0) + std::pow(this->Location.Y - (this->GridLocation.Y * 64 + 32), 2.0)) < 2)
		{
			this->Location.X = this->GridLocation.X * 64 + 32;
			this->Location.Y = this->GridLocation.Y * 64 + 32;
			if (this->WalkingQueue.size() > 0)
			{
				this->GridLocation = this->WalkingQueue.front();
				this->WalkingQueue.pop();
			}
		}

		float xOffs = 0, yOffs = 0;
		if (this->Location.X != (float)(this->GridLocation.X * 64 + 32))
		{
			xOffs = (float)(this->GridLocation.X * 64 + 32) - this->Location.X;
			this->Location.X += xOffs / std::abs(xOffs) * 1.5f;
			if (std::abs(xOffs) < 1.0f) xOffs = 0.0f;
		}
		if (this->Location.Y != (float)(this->GridLocation.Y * 64 + 32))
		{
			yOffs = (float)(this->GridLocation.Y * 64 + 32) - this->Location.Y;
			this->Location.Y += yOffs / std::abs(yOffs) * 1.5f;
			if (std::abs(yOffs) < 1.0f) yOffs = 0.0f;
		}
		if (xOffs + yOffs == 0)
		{
			this->CurrentAnimation->Stop();
			this->CurrentAnimation->Reset();
		}
		else if (xOffs != 0) ChangeDirection(xOffs > 0 ? RIGHT : LEFT);
		else ChangeDirection(yOffs > 0 ? DOWN : UP);

		CurrentAnimation->Update(deltaTime);
	}

	void Player::Draw(FPoint2D levelOffset)
	{
		this->CurrentAnimation->Draw(this->Location.X - levelOffset.X, this->Location.Y - levelOffset.Y);
	}
}