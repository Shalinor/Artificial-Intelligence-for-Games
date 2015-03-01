#pragma once

#define GLM_FORCE_PURE

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <vector>

#include "Node.h"
#include <iostream>
#include "SpriteBatch.h"
#include "Input.h"


using	glm::vec3;

class Graph
{
public:
			Graph(bool directed_);
	virtual	~Graph();

	void	AddNode(Node* node_);			//Add given node
	
	/*NEEDS TO BE WORKED*/
	void	RemoveNode(Node* node_);		//Remove given node
	/********************/


	Node*	FindNode(vec3 position_);		//Find node by value (position)

	void	AddEdge(Node* nodeAlpha_, Node* nodeBeta_/*, Edge data (cost, etc)*/);	//directed_ assumes nodeAlpha -> nodeBeta
	void	RemoveEdge(Node* nodeAlpha_, Node* nodeBeta_);
	void	DisplayToConsole();
	void	DisplayToScreen(SpriteBatch* spriteBatch_, Texture* texture_);

	void	Update();

protected:
	Input*	input; 
	
	bool	directed;
	bool	mouseLeftReleased;
	bool	mouseRightReleased;

	std::vector<Node*>	nodes;
};
