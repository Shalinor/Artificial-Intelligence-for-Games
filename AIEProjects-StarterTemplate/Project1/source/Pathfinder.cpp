#include "Pathfinder.h"

Pathfinder::Pathfinder(){}

void Pathfinder::Dijkstras(Node* start_, const std::list<Node*> &potentialEnd_, std::list<Node*> &outPath_)
{
	std::list<PathNode*>	openList;
	std::list<PathNode*>	closedList;

	//Reset the lists
	openList.clear();
	closedList.clear();

	//Reset the nodes
	/*for (auto iterator = nodes.begin(); iterator != nodes.end(); ++iterator)
	{
		(*iterator)->ClearDijkstrasValues();
	}*/

	PathNode* endNode = NULL;
	PathNode* currentNode = NULL;

	PathNode* pathStart = new PathNode();

	pathStart->node = start_;

	openList.push_back(pathStart);

	while (!openList.empty())
	{
		//Sort openList by Node.gScore
		openList.sort([](const PathNode* nodeA, const PathNode* nodeB){return nodeA->gScore < nodeB->gScore; });

		currentNode = openList.front();
		openList.pop_front();

		//Process Node...
		for (auto iterator = potentialEnd_.begin(); iterator != potentialEnd_.end(); ++iterator)
		{
			if (currentNode->node == (*iterator))
			{
				endNode = currentNode;// (*iterator);
				break;
			}
		}

		if (endNode != NULL)
		{
			break;
		}

		closedList.push_back(currentNode);


		//iterator == edge within currentNode->node
		for (auto iterator = currentNode->node->edges.begin(); iterator != currentNode->node->edges.end(); ++iterator)
		{
			bool inClosedList = false;
			bool inOpenList = false;

			//Test for presence within closedList
			for (auto cLIterator = closedList.begin(); cLIterator != closedList.end(); ++cLIterator)
			{
				if (((*iterator)->end) == ((*cLIterator)->node))
				{
					inClosedList = true;
					break;
				}
			}

			/*
			Taken out as other paths involving the same node are not nescesarily invalid <and I can't spell>???
			Though the nodes gScore will get screwy...
			*/
			////Test for presence within openList
			//for (auto oLIterator = openList.begin(); oLIterator != openList.end(); ++oLIterator)
			//{
			//	if ((iterator->connection) == (*oLIterator))
			//	{
			//		inOpenList = true;
			//		break;
			//	}
			//}

			if (!inClosedList && !inOpenList)
			{
				PathNode* temp = new PathNode();
				temp->node = (*iterator)->end;
				temp->gScore = currentNode->gScore + (*iterator)->GetCost();
				temp->parent = currentNode;
				openList.push_back(temp);
			}
		}
	}

	//Calculate Path
	outPath_.clear();		//Clear any pre-existing path

	std::list<vec3> path;	//For debug output...
	currentNode = endNode;
	while (currentNode != NULL)
	{
		outPath_.push_front(currentNode->node);
		path.push_front(currentNode->node->GetPosition());	//For debug output...
		currentNode = currentNode->parent;
	}

	//For debug output...
	for (auto iterator = path.begin(); iterator != path.end(); ++iterator)
	{
//		printf("%f, %f\n", (*iterator).x, (*iterator).y);
	}

	/*
	Procedure FindPathDijkstras(startNode, List of potentialEndNodes)

	Let openList be a List of Nodes
	Let closedList be a List of Nodes

	Let endNode be a Node set to NULL

	Add startNode to openList

	While openList is not empty

	Sort openList by Node.gScore

	Let currentNode = first item in openList

	// Process the node, do what you want with it. EG:
	if currentNode is one of the potentialEnd
	endNode = currentNode
	break out of loop

	remove currentNode from openList
	Add currentNode to closedList

	for all connections c in currentNode
	Add c.connection to openList if not in closedList
	c.connection.gScore = currentNode.gScore + c.cost
	c.connection.parent = currentNode


	// Calculate Path
	Let path be a List of Vector2
	Let currentNode = endNode;
	While currentNode != NULL
	Add currentNode.position to path
	currentNode = currentNode.parent
	*/
}
