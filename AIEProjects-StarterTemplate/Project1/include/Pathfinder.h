#pragma once

#include <list>

#include "Node.h"

class Pathfinder
{
public:
	//Constructor
			Pathfinder();

	//Destructor
			~Pathfinder();

	//The path finding function that we had in our graph class previously.
	void	Dijkstras(	Node* start_,
						const std::list<Node*> &potentialEnd,
						std::list<Node*> &outPath);

private:
	struct PathNode
	{
		//Pointer to the original node in the graph
		Node*		node;

		//Information required for pathfinding
		PathNode*	parent;
		int			degreesOfSeperation;
		float		gScore;
	};

	std::list<PathNode*>	openList;							/*Let openList be a List of Nodes*/
	std::list<PathNode*>	closedList;							/*Let closedList be a List of Nodes*/

	bool					currentlySearching;
};