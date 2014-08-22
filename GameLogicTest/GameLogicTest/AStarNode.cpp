//==============================================//
// GameLogicTest                                //
//                                              //
// Content: AStarNode class                     //
// File:    AStarNode.cpp                       //
//                                              //
// Copyright (c) 2014, Max Giller               //
//==============================================//

#include "AStarNode.h"

namespace GameLogicTest
{
	AStarNode::AStarNode(int xLocation, int yLocation)
	{
		this->X = xLocation;
		this->Y = yLocation;

		this->G = this->H = this->F = 0;

		this->Parent = NULL;
	}

	AStarNode::~AStarNode()
	{
	}

	/*Returns the sum of x-distance and the y-distance between the current node and another node. */
	int AStarNode::CalculateManhattanDistance(AStarNode* otherNode)
	{
		return (std::abs(otherNode->X - this->X) + std::abs(otherNode->Y - this->Y));
	}

	/*Returns 10 if the other node lies in a horizontal or vertical line with the current node or 14 if it lies in a diagonal line. */
	int AStarNode::CalculateNeighborDistance(AStarNode* otherNode)
	{
		return (this->X == otherNode->X || this->Y == otherNode->Y ? 10 : 14);
	}
}