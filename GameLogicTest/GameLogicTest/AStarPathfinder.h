//==============================================//
// GameLogicTest                                //
//                                              //
// Content: AStarPathfinder class               //
// File:    AStarPathfinder.h                   //
//                                              //
// Copyright (c) 2014, Max Giller               //
//==============================================//

#pragma once

#include <vector>
#include "AStarNode.h"

namespace GameLogicTest
{
	class AStarPathfinder
	{

	private:
		/* Recursively creates a path from the start node to the end node via parented nodes. */
		std::vector<AStarNode*> ConstructPath(std::vector<AStarNode*> closedList, AStarNode* endNode);

		void InsertInOpenList(std::vector<AStarNode*> openList, AStarNode* nodeToInsert);

	public:
		AStarPathfinder();
		~AStarPathfinder();

		/* Main function, to find a path between to given nodes. */
		std::vector<AStarNode*> FindPath(AStarNode* startNode, AStarNode* endNode);
	};
}