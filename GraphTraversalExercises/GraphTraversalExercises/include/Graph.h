#pragma once

#include <vector>
//#include <queue>
//#include <stack>
#include <list>

#include <stdio.h>

struct Vector2
{
	Vector2() : x(0.f), y(0.f) {}
	Vector2(float val_) : x(val_), y(val_) {}
	Vector2(float x_, float y_) : x(x_), y(y_) {}
	//Vector2(Vector2 pos_) : x(pos_.x), y(pos_.y) {}

	float	x, y;
};

class Graph
{
public:
	//predefine classes
	struct Node;

	struct Edge
	{
		Node	*connection;

		float	cost;

		//default constructor
		Edge() : connection(NULL), cost(0.f) {}

		//overloaded construct
		Edge(Node * node_) : connection(node_), cost(0) {}

		//overloaded construct
		Edge(Node * node_, float cost_) : connection(node_), cost(cost_) {}
	};

	struct Node
	{
		Vector2	pos;

		float	gScore;
		Node*	parent;

		std::vector<Graph::Edge> connections;

		//default constructor
		Node() : pos(0.f,0.f), gScore(0), parent(NULL) {}

		//overloaded constructor
		Node(Vector2 pos_) : pos(pos_), gScore(0), parent(NULL) {}

		//overloaded constructor
		Node(Vector2 pos_, float gScore_, Node* parent_) : pos(pos_), gScore(gScore_), parent(parent_) {}

		void ClearDjikstrasValues() { parent = NULL, gScore = 0.f; }
	};

	//Default Constructor
	Graph(){};

	//Destructor
	virtual ~Graph()
	{
		//make sure to delete all nodes added to the graph
		for (auto iterator = nodes.begin(); iterator != nodes.end(); ++iterator)
			delete (*iterator);

		nodes.clear();
	}

	//Add's a node at the given location, return the created node
	Node *AddNode(float xPos_, float yPos_)
	{
		nodes.push_back(new Node(Vector2(xPos_, yPos_)));
		return nodes.back();
	}

	//This function connects 2 nodes by adding an edge
	//Cost is automatically set to the distance between n1 and n2
	void AddConnection(Node* n1_, Node* n2_)
	{
		//Setup distance based cost...
		float cost = sqrtf((n2_->pos.x - n1_->pos.x) * (n2_->pos.x - n1_->pos.x) + (n2_->pos.y - n1_->pos.y) * (n2_->pos.y - n1_->pos.y));

		n1_->connections.push_back(Edge(n2_, cost));
		n2_->connections.push_back(Edge(n1_, cost));
	}

	//Searches the graph starting from the "start" node until one of the
	// "potential end node's" are found.
	// The resulting path is added to the "outPath" list.
	void FindDijkstrasPath(Node* start_,
		const std::list<Node*> &potentialEndNodes_);// , std::list<Node*> &outPath_);

	//Helper function, populates "outNodes" with nodes that are within a
	// circular area (xPos, yPos, radius)
	void FindNodesInRange(std::vector<Node*> &outNodes_, float xPos_, float yPos_, float radius_);
	

private:
	std::vector<Node*>		nodes;

	//std::queue<Graph::Node*>	openList;
	std::list<Graph::Node*>	openList;	//Made into a list to allow searching...
	std::list<Graph::Node*>	closedList;
};

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