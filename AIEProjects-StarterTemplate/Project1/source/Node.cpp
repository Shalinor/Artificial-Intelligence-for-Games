#include "Node.h"

//#include <stdlib.h>


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
	
	//Make a char* version of the id for potential display to screen
	displayableID = new char;
	_itoa_s(id, displayableID, sizeof(id), 10);

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
	if (!edges.empty())
	{
		for (std::vector<Edge*>::iterator i = edges.begin(); i != edges.end(); ++i)
		{
			//If requested edge already exists, don't add it again
			if (((*i)->start == start_) && ((*i)->end == end_))
			{
				return;	//Break out - bit dodge?
			}
		}
	}

	//No pre-existing edge matches so make a new one
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

void	Node::DisplayEdgeIDToConsole()
{
	for (int i = 0; i != edges.size(); ++i)
	{
		edges[i]->DisplayIDToConsole();
	}
}

void	Node::DisplayEdgesToScreen(SpriteBatch* spriteBatch_)
{
	for (int i = 0; i != edges.size(); ++i)
	{
		spriteBatch_->DrawLine(edges[i]->start->position.x, edges[i]->start->position.y, edges[i]->end->position.x, edges[i]->end->position.y);
	}
}

void	Node::DisplayEdgesToScreen(SpriteBatch* spriteBatch_, bool displayCosts_, bool displayDirections_, Font* font_)
{
	for (int i = 0; i != edges.size(); ++i)
	{
		spriteBatch_->DrawLine(edges[i]->start->position.x, edges[i]->start->position.y, edges[i]->end->position.x, edges[i]->end->position.y);

		if (displayCosts_)
		{
			float startX = edges[i]->start->position.x;
			float startY = edges[i]->start->position.y;
			float endX = edges[i]->end->position.x;
			float endY = edges[i]->end->position.y;

			float displayX = 0.f, displayY = 0.f;

			if (startX == endX)			//Vertical
			{
				displayX = startX + 1.f;
				displayY = startY + ((startY - endY) / 2.f);
			}
			else if (startY == endY)	//Horizontal
			{
				displayX = startX + ((startX - endX) / 2.f);
				displayY = startY + 1.f;
			}
			else						//Diagonal
			{
				displayX = startX + ((startX - endX) / 2.f);
				displayY = startY + ((startY - endY) / 2.f);
			}

			spriteBatch_->DrawString(font_, edges[i]->GetDisplayableCost(), displayX, displayY);
		}
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

void	Node::DisplayNodeToScreen(SpriteBatch* spriteBatch_, bool displayIDs_, Font* font_)
{
	if (displayIDs_)
	{
		spriteBatch_->DrawString(font_, displayableID, position.x - (5 + (5.f * (float)(strlen(displayableID)))), position.y - 11.f);
	}

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

	displayableCost = new char;
	sprintf_s(displayableCost, sizeof(displayableCost), "%i", (int)cost);
}

void Node::Edge::DisplayToConsole()
{
	std::cout << "\tEdge Detected: ";
	start->DisplayPosition();
	std::cout << " -> ";
	end->DisplayPosition();
	std::cout << "\n";
}

void Node::Edge::DisplayIDToConsole()
{
	std::cout << "\tEdge Detected: ";
	start->DisplayIDToConsole();
	std::cout << " -> ";
	end->DisplayIDToConsole();
	std::cout << " : " << cost << "\n";
}