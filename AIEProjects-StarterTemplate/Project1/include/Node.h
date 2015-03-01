#pragma once

#define GLM_FORCE_PURE

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <vector>

#include <iostream>

#include "SpriteBatch.h"

using	glm::vec3;

class Node
{
public:
			Node(vec3 position_);
			~Node();

	vec3	GetPosition(){ return position; }
	void	DisplayPosition();

	void	AddEdge(Node* start_, Node* end_);
	void	RemoveEdge(Node* start_, Node* end_);
	void	DisplayEdgesToConsole();
	void	DisplayEdgesToScreen(SpriteBatch* spriteBatch_, Texture* texture_);

	class Edge
	{
	public:
				Edge(Node* start_, Node* end_/*, Edge data (cost, etc)*/);
		void	DisplayToConsole();

		Node*	start;
		Node*	end;

		//Any relevant data...	If data is used, need to add Getter functions...
	};
	
	vec3				position;
	std::vector<Edge*>	edges;
};
