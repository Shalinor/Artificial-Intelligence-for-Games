#pragma once

#define GLM_FORCE_PURE

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <vector>
#include <deque>
#include <list>

#include "Node.h"
#include <iostream>
#include "SpriteBatch.h"
#include "Input.h"


using	glm::vec3;

class Graph
{
public:
			Graph(bool directed_, float detectionRadius_);
	virtual	~Graph();

	void	AddNode(Node* node_);			//Add given node
	
	/*NEEDS TO BE WORKED*/
	void	RemoveNode(Node* node_);		//Remove given node
	/********************/


	Node*	FindNode(vec3 position_);		//Find node by value (position)

	void	AddEdge(Node* nodeAlpha_, Node* nodeBeta_, float cost_ = -1.0f/*, Edge data (cost, etc)*/);	//directed_ assumes nodeAlpha -> nodeBeta
	void	FillAllEdges(int gridSize_, float range_, bool diagonals_, float cost_ = -1.0f);
	void	RemoveEdge(Node* nodeAlpha_, Node* nodeBeta_);
	void	DisplayToConsole();
	void	DisplayToScreen(SpriteBatch* spriteBatch_, Texture* texture_);
	void	DisplayToScreen(SpriteBatch* spriteBatch_);	//If Nodes already know their textures...
	void	DisplayToScreen(SpriteBatch* spriteBatch_, bool displayIDs, bool displayCosts, bool displayDirections, Font* font);

	void	Update();
	void	Update(Texture* t1_, Texture* t2_, float cost_ = -1.0f);

	void	TraverseDFS();
	void	TraverseBFS();

	void	ClearTraversal();

protected:
	Input*	input; 
	
	bool	directed;
	float	detectionRadius;
	bool	mouseLeftReleased;
	bool	mouseRightReleased;

	bool	traversed;

	std::vector<Node*>	nodes;
	std::deque<Node*>	traversal;

	std::list<Node*>	openList;
	std::list<Node*>	closedList;
};
