//==============================================//
// GameLogicTest                                //
//                                              //
// Content: AStarPathfinding class              //
// File:    AStarPathfinding.cpp                //
//                                              //
// Copyright (c) 2014, Max Giller               //
//==============================================//

#include "AStarPathfinder.h"

namespace GameLogicTest
{
	AStarPathfinder::AStarPathfinder()
	{
	}

	AStarPathfinder::~AStarPathfinder()
	{
	}

	std::vector<AStarNode*> AStarPathfinder::FindPath(AStarNode* startNode, AStarNode* endNode)
	{
		std::vector<AStarNode*> openList;
		std::vector<AStarNode*> closedList;

		openList.push_back(startNode);

		startNode->G = 0;
		startNode->F = (startNode->G + startNode->CalculateManhattanDistance(endNode));

		while (openList.size() > 0)
		{
			AStarNode* currentNode = openList.back();

			if (currentNode == endNode)
			{
				closedList.push_back(endNode);
				openList.clear();
				return ConstructPath(closedList, endNode);
			}

			//TODO: remove currentNode from openList
			closedList.push_back(currentNode);
			for each (AStarNode* neighborNode in currentNode->Neighbors)
			{
				if (std::find(closedList.begin(), closedList.end(), neighborNode) != closedList.end()) continue;

				int tempG = currentNode->G + currentNode->CalculateNeighborDistance(neighborNode);

				if (std::find(openList.begin(), openList.end(), neighborNode) == openList.end() || tempG < neighborNode->G)
				{
					neighborNode->Parent = currentNode;
					neighborNode->G = tempG;
					neighborNode->F = neighborNode->G + neighborNode->CalculateManhattanDistance(endNode);
					if (std::find(openList.begin(), openList.end(), neighborNode) == openList.end()) InsertInOpenList(openList, neighborNode);
				}
			}
		}
		closedList.clear();
		openList.clear();
		return std::vector<AStarNode*>();
	}

	std::vector<AStarNode*> AStarPathfinder::ConstructPath(std::vector<AStarNode*> closedList, AStarNode* endNode)
	{
		if (endNode == NULL) return std::vector<AStarNode*>();
		std::vector<AStarNode*> temp;

		if (std::find(closedList.begin(), closedList.end(), endNode) != closedList.end()) temp = ConstructPath(closedList, endNode->Parent);

		temp.push_back(endNode);
		return temp;
	}

	void AStarPathfinder::InsertInOpenList(std::vector<AStarNode*> openList, AStarNode* nodeToInsert)
	{
		for (std::vector<AStarNode*>::iterator iter = openList.begin(); iter != openList.end(); ++iter)
		{
			AStarNode* currentNode = (*iter);

			if (currentNode->F < nodeToInsert->F)
			{
				openList.insert(iter - 1, nodeToInsert);
				return;
			}
		}
		openList.push_back(nodeToInsert);
	}
}