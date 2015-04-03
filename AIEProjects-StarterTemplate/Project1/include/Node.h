#pragma once

#define GLM_FORCE_PURE

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <vector>

#include <iostream>

#include "SpriteBatch.h"

using	glm::vec3;

class Edge;

class Node
{
public:
			Node(vec3 position_);
			Node(vec3 position_, Texture* untraversed_, Texture* traversed_);
			~Node();

	vec3	GetPosition(){ return position; }
	void	DisplayPosition();

	void	AddEdge(Node* start_, Node* end_, float cost_);
	void	RemoveEdge(Node* start_, Node* end_);
	void	DisplayEdgesToConsole();
	void	DisplayEdgeIDToConsole();
	void	DisplayEdgesToScreen(SpriteBatch* spriteBatch_);
	void	DisplayNodeToScreen(SpriteBatch* spriteBatch_);

	void	DisplayIDToConsole();

	void	SetTraversed(){ traversed = true; }
	bool	GetTraversed(){ return traversed; }
	void	ClearTraversal(){ traversed = false; }


	Node*	GetLinkedNode(int edgeNumber_);
	int		GetNumberOfEdges(){ return edges.size(); }

	class Edge
	{
	public:
		//If cost not set to 0+, will be distance between nodes
		Edge(Node* start_, Node* end_, float cost_ = -1.f/*, Edge data (cost, etc)*/);
		void	DisplayToConsole();
		void	DisplayIDToConsole();

		Node*	start;
		Node*	end;

		float	GetCost(){ return cost; }

	private:
		//Any relevant data...	If data is used, need to add Getter functions...
		float	cost;
	};
	
	int					id;
	bool				traversed;
	Texture*			traversedTexture;
	Texture*			untraversedTexture;

	vec3				position;
	std::vector<Edge*>	edges;
};
