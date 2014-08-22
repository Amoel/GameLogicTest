//==============================================//
// GameLogicTest                                //
//                                              //
// Content: AStarNode class                     //
// File:    AStarNode.h                         //
//                                              //
// Copyright (c) 2014, Max Giller               //
//==============================================//

#pragma once

#include <vector>

namespace GameLogicTest
{
	/* Basic node for A*-Pathfinding. */
	class AStarNode
	{
	public:
		/* G = Distance of the Node from the start node.
		 * H = Manhattan-Distance from the node to the destination node (dX + dY).
		 * F = Sum of G and H;
		 */
		int G, H, F, X, Y;

		/* Pointer to the parent node, to backtrace the correct path after the completion of A*. */
		AStarNode* Parent;
		/* Neighboring nodes of the current node. */
		std::vector<AStarNode*> Neighbors;

		AStarNode(int xLocation, int yLocation);
		~AStarNode();

		/*Returns the sum of x-distance and the y-distance between the current node and another node. */
		int CalculateManhattanDistance(AStarNode* otherNode);

		/*Returns 10 if the other node lies in a horizontal or vertical line with the current node or 14 if it lies in a diagonal line. */
		int CalculateNeighborDistance(AStarNode* otherNode);
	};
}