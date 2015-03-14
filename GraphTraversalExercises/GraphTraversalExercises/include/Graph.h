#pragma once

#include <vector>
//#include <queue>
//#include <stack>
#include <list>

#include <stdio.h>

class Graph
{
public:
	//predefine classes
	struct Node;

	struct Edge
	{
		Node	*connection;

		//default constructor
		Edge() : connection(NULL) {}

		//overloaded construct
		Edge(Node * node) : connection(node) {}
	};

	struct Node
	{
		int		value;
		int		dos;	//Degrees of Seperation
		std::vector<Graph::Edge> connections;

		//default constructor
		Node() : value(0), dos(0) {}

		//overloaded constructor
		Node(int val, int ds) : value(val), dos(ds) {}

		void IncrementDOS(int inc)
		{
			dos = inc;
		}

		bool CompareNodes(const Graph::Node first, const Graph::Node second)
		{
			return first.dos < second.dos;
		}
	};

	~Graph()
	{
		//make sure to delete all nodes added to the graph
		for (auto iterator = nodes.begin(); iterator != nodes.end(); ++iterator)
			delete (*iterator);

		nodes.clear();
	}

	Node *AddNode(int value, int dos)
	{
		nodes.push_back(new Node(value, dos));
		return nodes.back();
	}

	void AddConnection(Node* n1, Node* n2)
	{
		n1->connections.push_back(Edge(n2));
		n2->connections.push_back(Edge(n1));
	}

	void ResetDOS();
	void TraverseGraph(Graph::Node* startNode);

	void PrintBFS();
	void PrintBFS(Graph::Node* startNode);

	void PrintDFS();
	void PrintDFS(Graph::Node* startNode);

private:
	std::vector<Node*>		nodes;

	//std::queue<Graph::Node*>	openList;
	std::list<Graph::Node*>	openList;	//Made into a list to allow searching...
	std::list<Graph::Node*>	closedList;
};

/*
//BFS Pseudocode	- DFS replace Queue to Stack
Procedure BFS(startNode)

	Let openList be a Queue
	Let closedList be a List

	Add startNode to openList

	While openList is not empty

		Let currentNode = next item in openList

		//Process the node, do what you want with it. EG:
		Print value of currentNode to console

		remove currentNode from openList
		Add currentNode to closedList

		for all connections c in currentNode
			if c is not on closedList
				let c.degreesOfSeperation = currentNode.degreesOfSeperation + 1	//This is added to allow for degrees of seperation
					Add c to openList if not in closedList
*/