#pragma once

#include <list>
#include <deque>
#include <limits>

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

	/*void	AStar(		Node*	start_,
						Node*	end_,
						std::list<Node*> &outPath_);*/

	void	AStarTutorial(Node*	start_, Node*	end_, std::list<Node*> &outPath_);

	void	AStarLecture(Node*	start_, Node*	end_, std::list<Node*> &outPath_);

	void	AStarWiki(Node*	start_, Node*	end_, std::list<Node*> &outPath_);

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
		float		hMultiplier;			//A* - Multiplier to be applied to the hScore
		float		fScore;					//A* - Final Score (gScore + hScore)

		PathNode()
		{
			node = NULL;
			parent = NULL;
			degreesOfSeperation = 0;
			gScore = std::numeric_limits<float>::infinity();
			hScore = 0.f;
			hMultiplier = 1.f;
			fScore = 0.f;
		}
	};

	std::deque<PathNode*>	openList;							/*Let openList be a List of Nodes*/
	std::deque<PathNode*>	closedList;							/*Let closedList be a List of Nodes*/

//	std::deque<Node*>		traversal;

	bool					currentlySearching;

	float	Get2DDistance(vec3 pointA_, vec3 pointB_);// { return sqrtf((distVector_.x * distVector_.x) + (distVector_.y * distVector_.y)); }

	/* I want to combine these with an enum indicating what swap we want*/
	void	swapLowestFScoreToFront();
	void	swapLowestGScoreToFront();
	void	swapLowestDOSToFront();
	void	swapHighestDOSToFront();
};