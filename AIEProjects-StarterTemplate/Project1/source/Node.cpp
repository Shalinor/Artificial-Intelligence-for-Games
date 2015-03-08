#include "Node.h"


Node::Node(vec3 position_)
{
	position = position_;
	traversed = false;
}

Node::Node(vec3 position_, Texture* untraversed_, Texture* traversed_)
{
	//Really bad, but just for testing the traversals against slides...
	static int id_ = -1;
	id = ++id_;

	position = position_;

	untraversedTexture = untraversed_;
	traversedTexture = traversed_;

	traversed = false;
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

void	Node::DisplayEdgesToScreen(SpriteBatch* spriteBatch_)
{
	for (int i = 0; i != edges.size(); ++i)
	{
		spriteBatch_->DrawLine(edges[i]->start->position.x, edges[i]->start->position.y, edges[i]->end->position.x, edges[i]->end->position.y);
	}
}

void	Node::DisplayNodeToScreen(SpriteBatch* spriteBatch_)
{
	if (traversed)
	{
		spriteBatch_->DrawSprite(traversedTexture, position.x, position.y, 10.f, 10.f);
	}
	else	//untraversed
	{
		spriteBatch_->DrawSprite(untraversedTexture, position.x, position.y, 10.f, 10.f);
	}
}

Node*	Node::GetLinkedNode(int edgeNumber_)
{
	if (edgeNumber_ <= edges.size())
	{
		return edges[edgeNumber_]->end;
	}

	else return NULL;
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