#include "Node.h"


Node::Node(vec3 position_)
{
	position = position_;
}

Node::~Node()
{
	edges.clear();
}

void	Node::AddEdge(Node* start_, Node* end_)
{
	edges.push_back(new Edge(start_, end_));	
}

void	Node::RemoveEdge(Node* start_, Node* end_)
{
	for (std::vector<Edge*>::iterator i = edges.begin(); i != edges.end(); ++i)
	{
		if (((*i)->start == start_) && ((*i)->end == end_))
		{
			edges.erase(i);
			return;	//Break out - bit dodge?
		}
	}
}

void	Node::DisplayPosition()
{
	std::cout << position.x << ", " << position.y << ", " << position.z;
}

void	Node::DisplayEdgesToConsole()
{
	for (int i = 0; i != edges.size(); ++i)
	{
		edges[i]->DisplayToConsole();
	}
}

void	Node::DisplayEdgesToScreen(SpriteBatch* spriteBatch_, Texture* texture_)
{
	for (int i = 0; i != edges.size(); ++i)
	{
		spriteBatch_->DrawLine(edges[i]->start->position.x, edges[i]->start->position.y, edges[i]->end->position.x, edges[i]->end->position.y);
	}
}



Node::Edge::Edge(Node* start_, Node* end_)
{
	start = start_;
	end = end_;
}

void Node::Edge::DisplayToConsole()
{
	std::cout << "\tEdge Detected: ";
	start->DisplayPosition();
	std::cout << " -> ";
	end->DisplayPosition();
	std::cout << "\n";
}