#pragma once

#include <vector>

//We can use whatever math library we want (eg, GLM)
//For now...
struct Vector2
{
	float x;
	float y;

	bool operator==(Vector2 data_)
	{
		if ((data_.x == x) && (data_.y == y))
		{
			return true;
		}

		return false;
	}
};

/*
 *
 * For my old brain - a Node is the object, an Edge is the link
 *
 */

class Graph
{
public:
	class Edge;
	class Node
	{
	public:
		Node(Vector2 data_);
		~Node();


		std::vector<Graph::Edge*>	edgeList;
		Vector2 data;
		//Add appropriate data
	};

	class Edge
	{
	public:
		Edge(Node* start_, Node* end_, float cost_);
		~Edge();

		Node* start;
		Node* end;
		//Add appropriate data

		float cost;
	};

	Graph();
	virtual ~Graph();

	Node *AddNode(Vector2 data_);
	Node *FindNode(Vector2 data_);	//Find node with value
	void RemoveNode(Node *pNode_);	//Remove the given node

	void ConnectNodes(Node *nodeA_, Node *nodeB_, float cost_/* edge data (cost or something) */);

protected:
	//List of Nodes
	// (which container type are you going to use)
	std::vector<Node*>	nodeList;
};