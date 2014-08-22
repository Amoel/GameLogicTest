//==============================================//
// GameLogicTest                                //
//                                              //
// Content: Enemy class                         //
// File:    Enemy.h                             //
//                                              //
// Copyright (c) 2014, Max Giller               //
//==============================================//

#pragma once

#include "Entity.h"

namespace GameLogicTest
{
	class Enemy : public Entity
	{
	private:

	public:
		Enemy(int x, int y);
		~Enemy();

		void Update(float deltaTime);
		void Draw(FPoint2D levelOffset);
	};
}