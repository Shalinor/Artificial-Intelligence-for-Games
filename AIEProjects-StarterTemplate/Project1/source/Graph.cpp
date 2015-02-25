#include "Graph.h"

Graph::Graph()
{
}

Graph::~Graph()
{
	nodeList.clear();
}

Graph::Node::Node(Vector2 data_)
{
	this->data = data_;
}

Graph::Node::~Node()
{
}

Graph::Edge::Edge(Node* start_, Node* end_, float cost_)
{
	this->start = start_;
	this->end = end_;
	this->cost = cost_;
}

Graph::Edge::~Edge()
{
	delete start;
	delete end;
}

Graph::Node* Graph::AddNode(Vector2 data_)
{
	Graph::Node* temp = new Graph::Node(data_);
	nodeList.push_back(temp);

	return temp;
}

Graph::Node* Graph::FindNode(Vector2 data_)
{
	for (int i = 0; i < nodeList.size(); ++i)
	{
		if (nodeList[i]->data == data_)
		{
			return nodeList[i];
		}
	}

	return NULL;
}

void Graph::RemoveNode(Node *pNode_)
{
	/*
	for (int iterator = nodeList.begin; iterator != nodeList.end; ++iterator)
	{
		if (nodeList[iterator] == pNode_)
		{
			//nodeList.erase(iterator);
		}
	}
	*/
}

void Graph::ConnectNodes(Node *nodeA_, Node *nodeB_, float cost_/* edge data (cost or something) */)
{
//	edgeList.push_back(Graph::Edge(nodeA_, nodeB_, cost_));
}

/*

class Graph
{
public:
	Graph();
	virtual ~Graph();

	Node *AddNode(Vector2 data_);
	Node *FindNode(Vector2 data_);	//Find node with value
	void RemoveNode(Node *pNode_);	//Remove the given node

	void ConnectNodes(Node *nodeA_, Node *nodeB_, int cost_/* edge data (cost or something) *///);
	/*
protected:
	//List of Nodes
	// (which container type are you going to use)
	std::vector<Node*>	nodeList;
};

*/