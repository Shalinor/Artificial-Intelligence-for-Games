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
	PathNode* openListVersion = NULL;

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
		pathStart->gScore = 0.f;

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
			if (!inClosedList)
			{
				for (auto oLIterator = openList.begin(); oLIterator != openList.end(); ++oLIterator)
				{
					if (((*iterator)->end) == ((*oLIterator)->node))
					{
						openListVersion = (*oLIterator);
						inOpenList = true;
						break;
					}
				}
			}

			if (!inClosedList && (*iterator)->end->GetTraversable())
			{
				(*iterator)->end->SetTraversed();

				if (inOpenList)
				{
					float tempGScore = currentNode->gScore + (*iterator)->GetCost();

					//					std::cout << "Current gScore: " << openListVersion->gScore << " vs new: " << tempGScore;

					if (tempGScore < openListVersion->gScore)
					{
						//						std::cout << "\n\tUpdating details G: " << openListVersion->gScore << " H: " << openListVersion->hScore << " F: " << openListVersion->fScore << std::endl;

						openListVersion->parent = currentNode;
						openListVersion->gScore = tempGScore;

						//						std::cout << "\tNew details G: " << openListVersion->gScore << " H: " << openListVersion->hScore << " F: " << openListVersion->fScore;
					}
				}
				else
				{
					PathNode* temp = new PathNode();
					temp->parent = currentNode;
					temp->node = (*iterator)->end;
					temp->gScore = currentNode->gScore + (*iterator)->GetCost();

					openList.push_back(temp);

					//					std::cout << "Adding Node: ID-" << temp->node->displayableID << " G-" << temp->gScore << " H-" << temp->hScore << " F-" << temp->fScore;

					temp = NULL;
					delete temp;
				}
			}
		}
	}

	if (openList.empty())	//Covers if no path found.
	{
		currentlySearching = false;
	}

	if (endNode != NULL)	//If openList is empty, search is complete (whether a path is found or not)...
	{
		//Debugging console output - final path gScore
		std::cout << "Dijkstra's path gScore: " << currentNode->gScore << "\n";

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

void Pathfinder::BFS_DFS(Node* startNode_, bool DFS_)
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

		if (!inClosedList && !inOpenList && (*iterator)->end->GetTraversable())
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

void Pathfinder::swapLowestFScoreToFront()		//Stolen/adapted from Jez :/
{
	for (auto &t : openList)
	{
		if (openList.front()->fScore > t->fScore)
		{
			//swap(tList.front(), t);
			std::swap(openList.front(), t);
		}
	}
}

void Pathfinder::swapLowestGScoreToFront()		//Stolen/adapted from Jez :/
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

void Pathfinder::swapLowestDOSToFront()			//Stolen/adapted from Jez :/
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

void Pathfinder::swapHighestDOSToFront()		//Stolen/adapted from Jez :/
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

float	Pathfinder::Get2DDistance(vec3 pointA_, vec3 pointB_)
{
	//return pointA_.x - pointB_.x + pointA_.y - pointB_.y;	//Manhattan Distance

	//return 0;	//Makes it into Dijkstra's

	//return (pointA_ - pointB_).length() * 1.f;
	
	vec3 distVector_ = pointA_ - pointB_;
	return sqrtf((distVector_.x * distVector_.x) + (distVector_.y * distVector_.y)) * 0.14f;
	//0.25f is nice - 45x45 off by 1 with random costs
	//with uniform costs, 0.1f makes a rounded search
	//with uniform costs, 0.125f makes a squared-to arrow search - faster than Dijkstra's, but still slow...
	//with uniform costs, 0.14f is nice - a rounded yet fairly direct path
}

//Tutorial pseudo code
void Pathfinder::AStarTutorial(Node* start_, Node* end_, std::list<Node*> &outPath_)
{
	//std::list<PathNode*>	openList;							/*Let openList be a List of Nodes*/
	//std::list<PathNode*>	closedList;							/*Let closedList be a List of Nodes*/

	PathNode* endNode = NULL;									/*Let endNode be a Node set to NULL*/
	PathNode* currentNode = NULL;
	PathNode* openListVersion = NULL;	//This is for storing the openList version of a node if duplicate found
	PathNode* temp = NULL;				//Stores the PathNode version of new node for openList, etc

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
		pathStart->gScore = 0.f;
		pathStart->hScore = Get2DDistance(start_->GetPosition(), end_->GetPosition());
		pathStart->fScore = pathStart->hScore;

		openList.push_back(pathStart);
	}

	//Always iterate through one node...
	//	while (!openList.empty())									/*While openList is not empty*/
	//	{
	/*Sort openList by Node.gScore*/
	//REPLACED LIST WITH DEQUE AND SWAPING LOWEST TO FRONT INSTEAD OF SORTING	openList.sort([](const PathNode* nodeA, const PathNode* nodeB){return nodeA->gScore < nodeB->gScore; });

	swapLowestFScoreToFront();

	currentNode = openList.front();							/*Let currentNode = first item in openList*/


	/*// Process the node, do what you want with it. EG:
	if currentNode is one of the potentialEnd
	endNode = currentNode
	break out of loop*/

	//Process Node...
	if (currentNode->node == end_)				/*if currentNode is the end_ node*/
	{
		endNode = currentNode;					/*endNode = currentNode*/
	}
	
	//If endNode is not NULL, a path has been found so stop searching
	if (endNode == NULL)
	{
		openList.pop_front();									/*Remove currentNode from openList*/
		closedList.push_back(currentNode);						/*Add currentNode to closedList*/


		/*  A* Exercise 1
		for all connections c in currentNode
			Let n = c.connection
			Add n to openList if not in closedList
			n.gScore = currentNode.gScore + c.cost
			n.hScore = distance from n to endNode
			n.fScore = n.gScore + n.hScore
			n.parent = currentNode
		*/

		/*	A* Exercise 2
		for all connections c in currentNode

			Let n = e.connection
			Let gScore = currentNode.gScore + e.cost

			If n.gScore < gScore or n.parent is null
				n.gScore = currentNode.gScore + e.cost
				n.hScore = distance from n to endNode
				n.fScore = n.gScore + n.hScore
				n.parent = currentNode

			Add n to openList if not in closedList
		*/


		//(*iterator) == edge/connection within currentNode->node			/*for all connections c in currentNode*/
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
			if (!inClosedList)
			{
				for (auto oLIterator = openList.begin(); oLIterator != openList.end(); ++oLIterator)
				{
					if (((*iterator)->end) == ((*oLIterator)->node))
					{
						inOpenList = true;
						openListVersion = (*oLIterator);
						break;
					}
				}
			}


			/*	A* Exercise 2
			for all edges <connections> e in currentNode

				Let n = e.connection
				Let gScore = currentNode.gScore + e.cost

				If n.gScore < gScore or n.parent is null
					n.gScore = currentNode.gScore + e.cost
					n.hScore = distance from n to endNode
					n.fScore = n.gScore + n.hScore
					n.parent = currentNode

				Add n to openList if not in closedList
			*/

			if (!inClosedList && (*iterator)->end->GetTraversable())
			{
				if (inOpenList)
				{
					float gScore = currentNode->gScore + (*iterator)->GetCost();

					if (openListVersion->gScore < gScore)		//Should this be '>'???
					{
						/*n.gScore = currentNode.gScore + c.cost*/
						openListVersion->gScore = gScore;//currentNode->gScore + (*iterator)->GetCost();
						/*n.hScore = distance from n to endNode*/
						vec3 nPos = openListVersion->node->GetPosition();
						vec3 endPos = end_->GetPosition();
						vec3 distVector = nPos - endPos;
						float distance = sqrtf((distVector.x * distVector.x) + (distVector.y * distVector.y));
						openListVersion->hScore = distance;
						/*n.fScore = n.gScore + n.hScore*/
						openListVersion->fScore = openListVersion->gScore + distance;//openListVersion->hScore;

						openListVersion->parent = currentNode;						/*c.connection.parent = currentNode*/
					}
				}
				else
				{
					temp = new PathNode();
					temp->node = (*iterator)->end;
					temp->node->SetTraversed();		//For display purposes only
					/*n.gScore = currentNode.gScore + c.cost*/
					temp->gScore = currentNode->gScore + (*iterator)->GetCost();
					/*n.hScore = distance from n to endNode*/
					vec3 nPos = temp->node->GetPosition();
					vec3 endPos = end_->GetPosition();
					vec3 distVector = nPos - endPos;
					float distance = sqrtf((distVector.x * distVector.x) + (distVector.y * distVector.y));
					temp->hScore = distance;
					/*n.fScore = n.gScore + n.hScore*/
					temp->fScore = temp->gScore + temp->hScore;

					temp->parent = currentNode;						/*c.connection.parent = currentNode*/
					openList.push_back(temp);						/*Add c.connection to openList if not in closedList*/
				}
			}
		}
	}

	if (openList.empty())	//Covers if no path found.
	{
		currentlySearching = false;
	}

	if (endNode != NULL)	//If openList is empty, search is complete (whether a path is found or not)...
	{
		//Debugging console output - final path gScore
		std::cout << "A*'s path gScore: " << currentNode->gScore << "\n";

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

//Lecture pseudo code
void Pathfinder::AStarLecture(Node* start_, Node* end_, std::list<Node*> &outPath_)
{
	PathNode* endNode = NULL;									/*Let endNode be a Node set to NULL*/
	PathNode* currentNode = NULL;
	PathNode* openListVersion = NULL;	//This is for storing the openList version of a node if duplicate found
	PathNode* temp = NULL;				//Stores the PathNode version of new node for openList, etc

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
		pathStart->gScore = 0.f;
		pathStart->hScore = Get2DDistance(start_->GetPosition(), end_->GetPosition());
		pathStart->fScore = pathStart->hScore;

		openList.push_back(pathStart);
	}

	//<sort> Put the lowest fScore to front of queue
	swapLowestFScoreToFront();

	currentNode = openList.front();							/*Let currentNode = first item in openList*/
	//openList.pop_front();									/*Remove currentNode from openList*/
	//currentNode->node->SetTraversed();						//Mark as traversed
	//closedList.push_back(currentNode);						/*Add currentNode to closedList*/
	
	
	/*// Process the node, do what you want with it. EG:
	if currentNode is one of the potentialEnd
	endNode = currentNode
	break out of loop*/
	
	//Process Node...
	if (currentNode->node == end_)				/*if currentNode is the end_ node*/
	{
		endNode = currentNode;					/*endNode = currentNode*/
	}
	
	//If endNode is not NULL, a path has been found so stop searching
	if (endNode == NULL)
	{
		openList.pop_front();									/*Remove currentNode from openList*/
		closedList.push_back(currentNode);						/*Add currentNode to closedList*/

		for (auto iterator = currentNode->node->edges.begin(); iterator != currentNode->node->edges.end(); ++iterator)
		{
			bool inClosedList = false;
			bool inOpenList = false;

			for (auto cLIterator = closedList.begin(); cLIterator != closedList.end(); ++cLIterator)
			{
				if ((*iterator)->end == (*cLIterator)->node)
				{
					inClosedList = true;
					break;								//Break out of closedList loop
				}
			}

			if (!inClosedList)
			{
				for (auto oLIterator = openList.begin(); oLIterator != openList.end(); ++oLIterator)
				{
					if ((*iterator)->end == (*oLIterator)->node)
					{
						inOpenList = true;
						openListVersion = (*oLIterator);	//To be used to test if new connection is better than previous
						break;								//Break out of openList loop
					}
				}
			}

			/*	A* Exercise 2
			for all connections c in currentNode

				Let n = e.connection
				Let gScore = currentNode.gScore + e.cost

				If n.gScore < gScore or n.parent is null
					n.gScore = currentNode.gScore + e.cost
					n.hScore = distance from n to endNode
					n.fScore = n.gScore + n.hScore
					n.parent = currentNode

				Add n to openList if not in closedList
			*/


			if (!inClosedList && (*iterator)->end->GetTraversable())
			{
				if (inOpenList)
				{
					vec3 nPos = openListVersion->node->GetPosition();
					vec3 endPos = end_->GetPosition();
					vec3 distVector = nPos - endPos;

					float currentNodesGScore = currentNode->gScore + (*iterator)->GetCost();
					float currentNodesHScore = Get2DDistance(openListVersion->node->GetPosition(), end_->GetPosition());
					float currentNodesFScore = currentNodesGScore + currentNodesHScore;

					if (currentNodesFScore < openListVersion->fScore)
					{
						openListVersion->parent = currentNode;
						openListVersion->gScore = currentNodesGScore;
						openListVersion->hScore = currentNodesHScore;
						openListVersion->fScore = currentNodesFScore;
					}
				}
				else	//!inOpenList
				{
					temp = new PathNode();
					temp->node = (*iterator)->end;
					temp->parent = currentNode;
					temp->gScore = currentNode->gScore + (*iterator)->GetCost();
					temp->hScore = Get2DDistance(temp->node->GetPosition(), end_->GetPosition());
					temp->fScore = temp->gScore + temp->hScore;
					temp->node->SetTraversed();						//Mark as traversed

					openList.push_back(temp);
					
					temp = NULL;
				}
			}
		}
	}
	/*
		Loop through its edges
			If end node not traversed	<in closedList>
				Calculate current node’s G + the edge cost + heuristic of end node
				If cost is less than existing F cost in end node
					Set end node’s N to the current node
					Set end node’s F to the current node’s G + the edge cost + heuristic of end node
					If end node not in the queue		<queue == openList>
						Push end node onto the queue	<queue == openList>
		*/



	if (openList.empty())	//Covers if no path found.
	{
		currentlySearching = false;
	}
		
	if (endNode != NULL)	//If openList is empty, search is complete (whether a path is found or not)...
	{
		//Debugging console output - final path gScore
		std::cout << "A*'s path gScore: " << currentNode->gScore << "\n";
		
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

//Wiki pseudo code
void Pathfinder::AStarWiki(Node* start_, Node* end_, std::list<Node*> &outPath_)
{
	PathNode* endNode = NULL;
	PathNode* currentNode = NULL;
	PathNode* openListVersion = NULL;

	if (!currentlySearching)
	{
		currentlySearching = true;

		closedList.clear();
		openList.clear();
		outPath_.clear();

//		std::cout << "Cleared lists for A*\n";

		PathNode* pathStart = new PathNode();

		pathStart->node = start_;
		pathStart->gScore = 0.f;
		pathStart->hScore = Get2DDistance(start_->GetPosition(), end_->GetPosition()) * pathStart->hMultiplier;
		pathStart->fScore = pathStart->hScore;

//		std::cout << "Added pathStart -> G: " << pathStart->gScore << " H: " << pathStart->hScore << " F: " << pathStart->fScore << std::endl;

		openList.push_back(pathStart);
	}

	
	swapLowestFScoreToFront();

	currentNode = openList.front();

	if (currentNode->node == end_)
	{
		currentlySearching = false;
		endNode = currentNode;

//		std::cout << "End found...  ID: " << currentNode->node->displayableID << " G: " << currentNode->gScore << std::endl;
	}
	
	
	if (endNode == NULL)
	{
//		std::cout << "Current Node: ID: " << currentNode->node->displayableID << " G: " << currentNode->gScore << " H: " << currentNode->hScore << " F: " << currentNode->fScore << std::endl;

		currentNode->node->SetTraversed();
		openList.pop_front();
		closedList.push_front(currentNode);

		for (auto iterator = currentNode->node->edges.begin(); iterator != currentNode->node->edges.end(); ++iterator)
		{
			bool	inClosedList = false;
			bool	inOpenList = false;

//			std::cout << "Checking Node " << (*iterator)->end->displayableID << " ";

			for (auto cLIterator = closedList.begin(); cLIterator != closedList.end(); ++cLIterator)
			{
				if ((*iterator)->end == (*cLIterator)->node)
				{
//					std::cout << " is in closedList";
					inClosedList = true;
					break;
				}
			}

			if (!inClosedList)
			{
				for (auto oLIterator = openList.begin(); oLIterator != openList.end(); ++oLIterator)
				{
					if ((*iterator)->end == (*oLIterator)->node)
					{
						//					std::cout << " is in openList";
						inOpenList = true;
						openListVersion = (*oLIterator);
						break;
					}
				}
			}

			if (!inClosedList && (*iterator)->end->GetTraversable())
			{
				(*iterator)->end->SetTraversed();

				if (inOpenList)
				{
					float tempGScore = currentNode->gScore + (*iterator)->GetCost();

//					std::cout << "Current gScore: " << openListVersion->gScore << " vs new: " << tempGScore;

					if (tempGScore < openListVersion->gScore)
					{
//						std::cout << "\n\tUpdating details G: " << openListVersion->gScore << " H: " << openListVersion->hScore << " F: " << openListVersion->fScore << std::endl;

						openListVersion->parent = currentNode;
						openListVersion->gScore = tempGScore;
						//hScore wont change, so not recalc'd
						openListVersion->fScore = openListVersion->gScore + openListVersion->hScore;

//						std::cout << "\tNew details G: " << openListVersion->gScore << " H: " << openListVersion->hScore << " F: " << openListVersion->fScore;
					}
				}
				else
				{
					PathNode* temp = new PathNode();
					temp->parent = currentNode;
					temp->node = (*iterator)->end;
					temp->gScore = currentNode->gScore + (*iterator)->GetCost();
					temp->hScore = Get2DDistance(temp->node->GetPosition(), end_->GetPosition()) * temp->hMultiplier;
					temp->fScore = temp->gScore + temp->hScore;

					openList.push_back(temp);

//					std::cout << "Adding Node: ID-" << temp->node->displayableID << " G-" << temp->gScore << " H-" << temp->hScore << " F-" << temp->fScore;

					temp = NULL;
					delete temp;
				}
			}

//			std::cout << std::endl;
		}
	}

	if (openList.empty())	//Covers if no path found.
	{
		currentlySearching = false;
	}
			
	if (endNode != NULL)	//If openList is empty, search is complete (whether a path is found or not)...
	{
		//Debugging console output - final path gScore
		std::cout << "A*'s path gScore: " << currentNode->gScore << "\n";
			
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

/*
function A*(start, goal)
			if neighbor in closedset
				continue
			tentative_g_score : = g_score[current] + dist_between(current, neighbor)

			if neighbor not in openset or tentative_g_score < g_score[neighbor]
				came_from[neighbor] : = current
				g_score[neighbor] : = tentative_g_score
				f_score[neighbor] : = g_score[neighbor] + heuristic_cost_estimate(neighbor, goal)
				if neighbor not in openset
					add neighbor to openset

	return failure

	
function reconstruct_path(came_from, current)
	total_path : = [current]
	while current in came_from :
		current : = came_from[current]
		total_path.append(current)
	return total_path
*/
}