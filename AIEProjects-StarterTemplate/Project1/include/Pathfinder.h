#pragma once

#include <list>
#include <deque>

#include "Node.h"

class Pathfinder
{
public:
	//Constructor
			Pathfinder();

	//Destructor
			~Pathfinder();

	//The path finding function that we had in our graph class previously.
	void	Dijkstras(	Node*					start_,
						const std::list<Node*>	&potentialEnd,
						std::list<Node*>		&outPath);

	void	ResetSearch(){ currentlySearching = false; }

	void	BFS_DFS(	Node*	startNode_,
						bool	DFS_);

	void	AStar(		Node*	start_,
						Node*	end_,
						std::list<Node*> &outPath_);

	//Don't use these - incorporated into the BFS_DFS above
//	void	BreadthFirstSearch(Node* startNode_);
//	void	DepthFirstSearch(Node* startNode_);

private:
	struct PathNode
	{
		//Pointer to the original node in the graph
		Node*		node;

		//Information required for pathfinding
		PathNode*	parent;
		int			degreesOfSeperation;	//BFS & DFS - Don't think it actually does anything
		float		gScore;					//Dijkstra's
		float		hScore;					//A* - Huristic
		float		fScore;					//A* - Final Score (gScore + hScore)
	};

	std::deque<PathNode*>	openList;							/*Let openList be a List of Nodes*/
	std::deque<PathNode*>	closedList;							/*Let closedList be a List of Nodes*/

//	std::deque<Node*>		traversal;

	bool					currentlySearching;


	/* I want to combine these with an enum indicating what swap we want*/
	void	swapLowestFScoreToFront();
	void	swapLowestGScoreToFront();
	void	swapLowestDOSToFront();
	void	swapHighestDOSToFront();
};