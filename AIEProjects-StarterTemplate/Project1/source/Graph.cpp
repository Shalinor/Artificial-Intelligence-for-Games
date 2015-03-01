#include "Graph.h"


Graph::Graph(bool directed_)
{
	directed = directed_;
}


Graph::~Graph()
{
	nodes.clear();
}

void Graph::AddNode(Node* node_)
{
	//Do we need to check for pre-existing node???
	nodes.push_back(node_);
}

/*NEEDS TO BE WORKED*/
void Graph::RemoveNode(Node* node_)
{
	std::vector<Node*>::iterator temp;

	//iterate through nodes and call removeEdge on each passing in (*i) as start_ and node_ as end_
	for (std::vector<Node*>::iterator i = nodes.begin(); i != nodes.end(); ++i)
	{
		(*i)->RemoveEdge((*i), node_);

		if ((*i) == node_)
		{
			temp = i;
		}
	}

	nodes.erase(temp);
}

Node* Graph::FindNode(vec3 position_)
{
	for (std::vector<Node*>::iterator i = nodes.begin(); i != nodes.end(); ++i)
	{
		if ((*i)->position == position_)
		{
			return (*i);
		}
	}

	//Not found
	return NULL;
}

void Graph::AddEdge(Node* nodeAlpha_, Node* nodeBeta_)
{
	nodeAlpha_->AddEdge(nodeAlpha_, nodeBeta_);

	//directed_ assumes nodeAlpha -> nodeBeta only
	if (!directed)
	{
		nodeBeta_->AddEdge(nodeBeta_, nodeAlpha_);
	}
}

void Graph::RemoveEdge(Node* nodeAlpha_, Node* nodeBeta_)
{
	nodeAlpha_->RemoveEdge(nodeAlpha_, nodeBeta_);

	//directed_ assumes nodeAlpha -> nodeBeta only
	if (!directed)
	{
		nodeBeta_->RemoveEdge(nodeBeta_, nodeAlpha_);
	}
}

void	Graph::DisplayToConsole()
{
	for (int i = 0; i != nodes.size(); ++i)
	{
		std::cout << "Node ";
		nodes[i]->DisplayPosition();
		std::cout << "\n";

		nodes[i]->DisplayEdgesToConsole();
	}
}

void	Graph::DisplayToScreen(SpriteBatch* spriteBatch_, Texture* texture_)
{
	for (int i = 0; i != nodes.size(); ++i)
	{
		nodes[i]->DisplayEdgesToScreen(spriteBatch_, texture_); 
		spriteBatch_->DrawSprite(texture_, nodes[i]->position.x, nodes[i]->position.y, 10.f, 10.f);
	}
}
