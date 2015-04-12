#include "Pathfinder.h"

Pathfinder::Pathfinder(){ currentlySearching = false; }

Pathfinder::~Pathfinder()
{
	//for (auto iterator = nodes.begin(); iterator != nodes.end(); ++iterator)
	//{
	//	delete (*iterator);
	//}

	///*for (auto iterator = traversal.begin(); iterator != traversal.end(); ++iterator)
	//{
	//delete (*iterator);
	//}*/

	//nodes.clear();
	////	traversal.clear();
}

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
//REPLACED LIST WITH DEQUE AND SWAPING LOWEST TO FRONT INSTEAD OF SORTING	openList.sort([](const PathNode* nodeA, const PathNode* nodeB){return nodeA->gScore < nodeB->gScore; });

	swapLowestGScoreToFront();

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
			bool inOpenList = false;

			//Test for presence within closedList				/*Add c.connection to openList if not in closedList*/
			for (auto cLIterator = closedList.begin(); cLIterator != closedList.end(); ++cLIterator)
			{
				if (((*iterator)->end) == ((*cLIterator)->node))
				{
					inClosedList = true;
					break;
				}
			}

			//Test for presence within openList					/*NOT in tutorial, but is in lecture note AND Sam said to do it <email 07-04-15>*/
			for (auto oLIterator = openList.begin(); oLIterator != openList.end(); ++oLIterator)
			{
				if (((*iterator)->end) == ((*oLIterator)->node))
				{
					inOpenList = true;
					break;
				}
			}

			if (!inClosedList && !inOpenList)
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

void	Pathfinder::BFS_DFS(Node* startNode_, bool DFS_)
{
	PathNode* currentNode = NULL;

	//If first instance of search, set it up
	if (!currentlySearching)
	{
		currentlySearching = true;

		//Reset the lists
		openList.clear();
		closedList.clear();

		PathNode* pathStart = new PathNode();
		pathStart->node = startNode_;								/*Add startNode to openList*/
		pathStart->degreesOfSeperation = 0;

		openList.push_back(pathStart);
	}

	if (DFS_)
	{
		//DFS - sort descending
		swapHighestDOSToFront();
	}
	else
	{
		//BFS - sort ascending
		swapLowestDOSToFront();
	}
	
	currentNode = openList.front();									/*Let currentNode = first item in openList*/

	openList.pop_front();											/*Remove currentNode from openList*/
	closedList.push_back(currentNode);								/*Add currentNode to closedList*/

	//Process the node, do what you want with it...
	currentNode->node->SetTraversed();		//For display purposes only

	/*
	for all connections c in currentNode
		if c is not on closedList
			let c.degreesOfSeporation = currentNode.degreesOfSeporation + 1
			Add c to openList
	*/


	//(*iterator) == edge within currentNode->node			/*for all connections c in currentNode*/
	for (auto iterator = currentNode->node->edges.begin(); iterator != currentNode->node->edges.end(); ++iterator)
	{
		bool inClosedList = false;
		bool inOpenList = false;

		//Test for presence within closedList				/*Add c.connection to openList if not in closedList*/
		for (auto cLIterator = closedList.begin(); cLIterator != closedList.end(); ++cLIterator)
		{
			if (((*iterator)->end) == ((*cLIterator)->node))
			{
				inClosedList = true;
				break;
			}
		}

		//Test for presence within openList					/*NOT in tutorial, but is in lecture note AND Sam said to do it <email 07-04-15>*/
		for (auto oLIterator = openList.begin(); oLIterator != openList.end(); ++oLIterator)
		{
			if (((*iterator)->end) == ((*oLIterator)->node))
			{
				inOpenList = true;
				break;
			}
		}

		if (!inClosedList && !inOpenList)
		{
			PathNode* temp = new PathNode();
			temp->node = (*iterator)->end;
			temp->degreesOfSeperation = currentNode->degreesOfSeperation + 1;
			openList.push_back(temp);						/*Add c.connection to openList if not in closedList*/
		}
	}

	if (openList.empty())
	{
		ResetSearch();
	}
}

void Pathfinder::swapLowestGScoreToFront()		//Stolen from Jez :/
{
	for (auto &t : openList)
	{
		if (openList.front()->gScore > t->gScore)
		{
			//swap(tList.front(), t);
			std::swap(openList.front(), t);
		}
	}
}

void Pathfinder::swapLowestDOSToFront()
{
	for (auto &t : openList)
	{
		if (openList.front()->degreesOfSeperation > t->degreesOfSeperation)
		{
			//swap(tList.front(), t);
			std::swap(openList.front(), t);
		}
	}
}

void Pathfinder::swapHighestDOSToFront()
{
	for (auto &t : openList)
	{
		if (openList.front()->degreesOfSeperation < t->degreesOfSeperation)
		{
			//swap(tList.front(), t);
			std::swap(openList.front(), t);
		}
	}
}


void Pathfinder::AStar(Node* start_, Node* end_)
{

}

/*
Procedure FindAStar(startNode, endNode)							*** New for A* ***
	Let openList be a List of Nodes
	Let closedList be a List of Nodes
	
	Add startNode to openList
	
	While openList is not empty
		Sort openList by Node.fScore
		
		Let currentNode = first item in openList
		
		// Process the node, do what you want with it. EG:
		if currentNode equals endNode							*** New for A* ***
			break out of loop									*** New for A* ***
			
		remove currentNode from openList
		Add currentNode to closedList
		
		for all Edges e in currentNode
			Let n = e.connection
			Add n to openList if not in closedList
			n.gScore = currentNode.gScore + e.cost				*** New for A* ***
			n.hScore = distance from n to endNode				*** New for A* ***
			n.fScore = n.gScore + n.hScore						*** New for A* ***
			n.parent = currentNode
			
		
	// Calculate Path
	Let path be a List of Vector2
	Let currentNode = endNode;
	While currentNode != NULL
		Add currentNode.position to path
		currentNode = currentNode.parent
*/