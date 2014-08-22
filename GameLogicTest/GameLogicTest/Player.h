//==============================================//
// GameLogicTest                                //
//                                              //
// Content: Player class                        //
// File:    Player.h                            //
//                                              //
// Copyright (c) 2014, Max Giller               //
//==============================================//

#pragma once

#include "Entity.h"

namespace GameLogicTest
{
	class Player : public Entity
	{
	private:

	public:
		int Lifes;

		Player(int life);
		~Player();

		void ChangeDirection(CharacterFaceDirection newDirection);

		void MoveToTile(int x, int y);
		void Update(float deltaTime);
		void Draw(FPoint2D levelOffset);
	};
}