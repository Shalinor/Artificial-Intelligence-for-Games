#include "Graph.h"

//Searches the graph starting from the "start" node until one of the
// "potential end node's" are found.
// The resulting path is added to the "outPath" list.
void Graph::FindDijkstrasPath(Node* start_,
	const std::list<Node*> &potentialEndNodes_)// , std::list<Node*> &outPath_)
{
	//Reset the lists
	openList.clear();
	closedList.clear();
	
	//Reset the nodes
	for (auto iterator = nodes.begin(); iterator != nodes.end(); ++iterator)
	{
		(*iterator)->ClearDjikstrasValues();
	}

	Node* endNode = NULL;
	Node* currentNode = NULL;

	openList.push_back(start_);

	while (!openList.empty())
	{
		//Sort openList by Node.gScore
		openList.sort([](const Node* nodeA, const Node* nodeB){return nodeA->gScore < nodeB->gScore; });

		currentNode = openList.front();
		openList.pop_front();

		//Process Node...
		for (auto iterator = potentialEndNodes_.begin(); iterator != potentialEndNodes_.end(); ++iterator)
		{
			endNode = (*iterator);
			break;	//Only breaks out of for?? may just clear openList??? or after for, if(endNode){break;}???
		}
		

		closedList.push_back(currentNode);


		for (auto iterator = currentNode->connections.begin(); iterator != currentNode->connections.end(); ++iterator)
		{
			bool inClosedList = false;
			bool inOpenList = false;

			//Test for presence within closedList
			for (auto cLIterator = closedList.begin(); cLIterator != closedList.end(); ++cLIterator)
			{
				if ((iterator->connection) == (*cLIterator))
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
				iterator->connection->gScore = currentNode->gScore + iterator->cost;
				iterator->connection->parent = currentNode;
				openList.push_back(iterator->connection);
			}
		}
	}

	//Calculate Path
	std::list<Vector2> path;
	currentNode = endNode;
	while (currentNode != NULL)
	{
		path.push_front(currentNode->pos);
		currentNode = currentNode->parent;
	}

	for (auto iterator = path.begin(); iterator != path.end(); ++iterator)
	{
		printf("%i, %i\n", (*iterator).x, (*iterator).y);
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

//Helper function, populates "outNodes" with nodes that are within a
// circular area (xPos, yPos, radius)
void Graph::FindNodesInRange(std::vector<Node*> &outNodes_, float xPos_, float yPos_, float radius_)
{

}


/*void Graph::TraverseGraph(Graph::Node* startNode_, bool breadthFirst_)
{
	//Reset the lists & nodes
	openList.clear();
	closedList.clear();
	ResetDOS();
	
	int increment = 0;

	openList.push_back(startNode_);

	while (!openList.empty())
	{
		if (breadthFirst_)
		{
			//sort openList ascending
			openList.sort([](const Graph::Node *nodeA, const Graph::Node *nodeB){ return nodeA->dos < nodeB->dos; });
		}	
		else//Depth first then
		{
			//sort openList descending
			openList.sort([](const Graph::Node *nodeA, const Graph::Node *nodeB){ return nodeA->dos > nodeB->dos; });
		}

		Graph::Node* currentNode = openList.front();
		openList.pop_front();

		//Process Node...
		printf("%c, %i\n", currentNode->value, currentNode->dos);

		closedList.push_back(currentNode);

		for (auto conIterator = currentNode->connections.begin(); conIterator != currentNode->connections.end(); ++conIterator)
		{
			bool inClosedList = false;
			bool inOpenList = false;

			//Test for presence within closedList
			for (auto cLIterator = closedList.begin(); cLIterator != closedList.end(); ++cLIterator)
			{
				if ((conIterator->connection) == (*cLIterator))
				{
					inClosedList = true;
					break;
				}
			}

			//Test for presence within openList
			for (auto oLIterator = openList.begin(); oLIterator != openList.end(); ++oLIterator)
			{
				if ((conIterator->connection) == (*oLIterator))
				{
					inOpenList = true;
					break;
				}
			}

			if (!inClosedList && !inOpenList)
			{
				conIterator->connection->IncrementDOS(++increment);
				openList.push_back(conIterator->connection);
			}
		}
	}
}
*/
