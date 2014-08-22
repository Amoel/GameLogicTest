//==============================================//
// GameLogicTest                                //
//                                              //
// Content: Tile struct                         //
// File:    Tile.h                              //
//                                              //
// Copyright (c) 2014, Max Giller               //
//==============================================//

#pragma once

#include "AStarNode.h"

namespace GameLogicTest
{
	enum TileState { DARK_PENAL, LIGHT_PENAL, TRAP };

	struct Tile
	{
		TileState State;
		AStarNode* Node;

		Tile() : State(TileState::DARK_PENAL), Node(NULL) {}
	};
}