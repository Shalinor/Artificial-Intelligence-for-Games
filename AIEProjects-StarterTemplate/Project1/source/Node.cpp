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

Node::Node(vec3 position_, float gScore_, Texture* untraversed_, Texture* traversed_)
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
	for (auto iterator = edges.begin(); iterator != edges.end(); ++iterator)
	{
		delete (*iterator);
	}

	edges.clear();
}

void	Node::AddEdge(Node* start_, Node* end_, float cost_)
{
	edges.push_back(new Edge(start_, end_, cost_));
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

void	Node::DisplayEdgeCostToConsole()
{
	for (int i = 0; i != edges.size(); ++i)
	{
		edges[i]->DisplayCostToConsole();
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

void	Node::DisplayIDToConsole()
{
	std::cout << id;
}

Node*	Node::GetLinkedNode(int edgeNumber_)
{
	if (edgeNumber_ <= edges.size())
	{
		return edges[edgeNumber_]->end;
	}

	else return NULL;
}



Node::Edge::Edge(Node* start_, Node* end_, float cost_)
{
	start = start_;
	end = end_;
	if (cost_ < 0)
	{
		cost = sqrtf((end_->position.x - start_->position.x) * (end_->position.x - start_->position.x) + (end_->position.y - start_->position.y) * (end_->position.y - start_->position.y));
	}
	else
	{
		cost = cost_;
	}
}

void Node::Edge::DisplayToConsole()
{
	std::cout << "\tEdge Detected: ";
	start->DisplayPosition();
	std::cout << " -> ";
	end->DisplayPosition();
	std::cout << "\n";
}

void Node::Edge::DisplayCostToConsole()
{
	std::cout << "\tEdge Detected: ";
	start->DisplayIDToConsole();
	std::cout << " -> ";
	end->DisplayIDToConsole();
	std::cout << " : " << cost << "\n";
}