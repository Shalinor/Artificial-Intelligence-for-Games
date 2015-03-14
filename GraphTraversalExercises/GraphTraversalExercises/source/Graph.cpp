#include "Graph.h"

void Graph::ResetDOS()
{
	for (auto iterator = nodes.begin(); iterator != nodes.end(); ++iterator)
	{
		(*iterator)->dos = 0;
	}
}

void Graph::TraverseGraph(Graph::Node* startNode)
{
	if (!openList.empty())
	{
		openList.clear();
		closedList.clear();
		ResetDOS();
	}

	int increment = 0;

	openList.push_back(startNode);

	while (!openList.empty())
	{
		Graph::Node* currentNode = openList.front();
		openList.pop_front();

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

void Graph::PrintBFS()
{
	if (!openList.empty())
	{
		openList.sort(Graph::Node::CompareNodes);
	}

	for (auto iterator = openList.begin(); iterator != openList.end(); ++iterator)
	{
		printf("%c, %i\n", (*iterator)->value, (*iterator)->dos);
	}
}

void Graph::PrintBFS(Graph::Node* startNode)
{
	//std::queue<Graph::Node*>	openList;
	std::list<Graph::Node*>		openList;	//Made into a list to allow searching...
	std::list<Graph::Node*>		closedList;

	int							increment = 0;

	openList.push_back(startNode);

	while (!openList.empty())
	{
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

void Graph::PrintDFS(Graph::Node* startNode)
{
	//std::stack<Graph::Node*>	openList;
	std::list<Graph::Node*>		openList;	//Made into a list to allow searching...
	std::list<Graph::Node*>		closedList;

	int							increment = nodes.size();

	openList.push_back(startNode);

	while (!openList.empty())
	{
		Graph::Node* currentNode = openList.back();
		openList.pop_back();

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
				conIterator->connection->IncrementDOS(--increment);
				openList.push_back(conIterator->connection);
			}
		}
	}
}
