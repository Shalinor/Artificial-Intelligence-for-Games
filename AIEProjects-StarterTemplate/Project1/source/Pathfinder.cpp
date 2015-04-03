#include "Pathfinder.h"

Pathfinder::Pathfinder(){ currentlySearching = false; }

void Pathfinder::Dijkstras(Node* start_, const std::list<Node*> &potentialEnd_, std::list<Node*> &outPath_)
{
	//std::list<PathNode*>	openList;							/*Let openList be a List of Nodes*/
	//std::list<PathNode*>	closedList;							/*Let closedList be a List of Nodes*/

	PathNode* endNode = NULL;									/*Let endNode be a Node set to NULL*/
	PathNode* currentNode = NULL;

	//If first instance of search, set it up
	if (!currentlySearching)
	{
		currentlySearching = true;

		//Reset the lists
		openList.clear();
		closedList.clear();
		outPath_.clear();

		//Reset the nodes' traversal flag


		//PathNode* endNode = NULL;									/*Let endNode be a Node set to NULL*/
		//PathNode* currentNode = NULL;

		PathNode* pathStart = new PathNode();

		pathStart->node = start_;									/*Add startNode to openList*/

		openList.push_back(pathStart);
	}

//Always iterate through one node...
//	while (!openList.empty())									/*While openList is not empty*/
//	{
																/*Sort openList by Node.gScore*/
	openList.sort([](const PathNode* nodeA, const PathNode* nodeB){return nodeA->gScore < nodeB->gScore; });

	currentNode = openList.front();							/*Let currentNode = first item in openList*/


															/*// Process the node, do what you want with it. EG:
																if currentNode is one of the potentialEnd
																	endNode = currentNode
																	break out of loop*/

	//Process Node...
	for (auto iterator = potentialEnd_.begin(); iterator != potentialEnd_.end(); ++iterator)
	{
		if (currentNode->node == (*iterator))				/*if currentNode is one of the potentialEnd*/
		{
			endNode = currentNode;							/*endNode = currentNode*/
			break;											/*break out of loop*/
		}
	}

	//If endNode is not NULL, a path has been found so stop searching
	if (endNode == NULL)
	{
		openList.pop_front();									/*Remove currentNode from openList*/
		closedList.push_back(currentNode);						/*Add currentNode to closedList*/


		/*for all connections c in currentNode
				Add c.connection to openList if not in closedList
				c.connection.gScore = currentNode.gScore + c.cost
				c.connection.parent = currentNode*/


		//(*iterator) == edge within currentNode->node			/*for all connections c in currentNode*/
		for (auto iterator = currentNode->node->edges.begin(); iterator != currentNode->node->edges.end(); ++iterator)
		{
			bool inClosedList = false;
			//bool inOpenList = false;

			//Test for presence within closedList				/*Add c.connection to openList if not in closedList*/
			for (auto cLIterator = closedList.begin(); cLIterator != closedList.end(); ++cLIterator)
			{
				if (((*iterator)->end) == ((*cLIterator)->node))
				{
					inClosedList = true;
					break;
				}
			}

			if (!inClosedList)// && !inOpenList)
			{
				PathNode* temp = new PathNode();
				temp->node = (*iterator)->end;
				temp->node->SetTraversed();		//For display purposes only
				/*c.connection.gScore = currentNode.gScore + c.cost*/
				temp->gScore = currentNode->gScore + (*iterator)->GetCost();
				temp->parent = currentNode;						/*c.connection.parent = currentNode*/
				openList.push_back(temp);						/*Add c.connection to openList if not in closedList*/
			}
		}
	}
//	}

	if (openList.empty())	//Covers if no path found.
	{
		currentlySearching = false;
	}

	if (endNode != NULL)	//If openList is empty, search is complete (whether a path is found or not)...
	{
		currentlySearching = false;	//Search is completed
		//Calculate Path											/*//Calculate Path*/
		outPath_.clear();		//Clear any pre-existing path		/*Let path be a List of Vector2*/

		currentNode = endNode;										/*Let currentNode = endNode;*/
		while (currentNode != NULL)									/*While currentNode != NULL*/
		{
			outPath_.push_front(currentNode->node);					/*Add currentNode.position to path*/ //<-path was for debug output
			currentNode = currentNode->parent;						/*currentNode = currentNode.parent*/
		}
	}
}
