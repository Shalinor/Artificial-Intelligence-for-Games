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
			Node(vec3 position_, Texture* untraversed__, Texture* traversed__);
			~Node();

	vec3	GetPosition(){ return position; }
	void	DisplayPosition();

	void	AddEdge(Node* start_, Node* end_);
	void	RemoveEdge(Node* start_, Node* end_);
	void	DisplayEdgesToConsole();
	void	DisplayEdgesToScreen(SpriteBatch* spriteBatch_);
	void	DisplayNodeToScreen(SpriteBatch* spriteBatch_);

	void	SetTraversed(){ traversed = true; }
	bool	GetTraversed(){ return traversed; }
	void	ClearTraversal(){ traversed = false; }


	Node*	GetLinkedNode(int edgeNumber_);
	int		GetNumberOfEdges(){ return edges.size(); }

	class Edge
	{
	public:
				Edge(Node* start_, Node* end_/*, Edge data (cost, etc)*/);
		void	DisplayToConsole();

		Node*	start;
		Node*	end;

		//Any relevant data...	If data is used, need to add Getter functions...
	};
	
	int					id;
	bool				traversed;
	Texture*			traversedTexture;
	Texture*			untraversedTexture;

	vec3				position;
	std::vector<Edge*>	edges;
};
