//==============================================//
// GameLogicTest                                //
//                                              //
// Content: Enemy class                         //
// File:    Enemy.cpp                           //
//                                              //
// Copyright (c) 2014, Max Giller               //
//==============================================//

#include "Enemy.h"

namespace GameLogicTest
{
	/* Enemy class, x and y are the coordinates where the enemy will spawn on the map. */
	Enemy::Enemy(int x, int y)
	{
		Spritesheet = al_load_bitmap("Graphics/gfx_enemySpritesheet.png");

		Animations = std::map<CharacterFaceDirection, Animation*>();

		/* Creates four Animations, each with a section of Spritesheet for the four direction an enemy can look at. */
		this->Animations.insert(std::pair<CharacterFaceDirection, Animation*>(UP, new Animation(Spritesheet, 3, 4, 9, 11)));
		this->Animations.insert(std::pair<CharacterFaceDirection, Animation*>(DOWN, new Animation(Spritesheet, 3, 4, 0, 2)));
		this->Animations.insert(std::pair<CharacterFaceDirection, Animation*>(LEFT, new Animation(Spritesheet, 3, 4, 3, 5)));
		this->Animations.insert(std::pair<CharacterFaceDirection, Animation*>(RIGHT, new Animation(Spritesheet, 3, 4, 6, 8)));

		/* Let the current animation point to the DOWN animation, so the enemy looks down when the game starts. */
		CurrentAnimation = Animations.find(DOWN)->second;
		CurrentAnimation->Start();

		GridLocation = Point2D{ x, y };
		Location = FPoint2D{ x * 64 + 32, y * 64 + 32 };

		this->WalkingQueue = std::queue<Point2D>();
	}

	Enemy::~Enemy()
	{

	}

	void Enemy::Update(float deltaTime)
	{
		CurrentAnimation->Update(deltaTime);
	}

	void Enemy::Draw(FPoint2D levelOffset)
	{
		this->CurrentAnimation->Draw(this->Location.X - levelOffset.X, this->Location.Y - levelOffset.Y);
	}
}