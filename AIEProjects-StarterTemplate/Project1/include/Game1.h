
/*-----------------------------------------------------------------------------
Author:			
Description:	
-----------------------------------------------------------------------------*/
#ifndef GAME1_H
#define GAME1_H

#include <list>

#include "Application.h"
#include "Pathfinder.h"

class SpriteBatch;
class Texture;		//<- I don't like this method, I know it avoids polluting namespace, but meh...
class Graph;
class Node;
class Input;

class Game1 : public Application
{
public:

	// assets loaded in constructor
	Game1(unsigned int windowWidth, unsigned int windowHeight, bool fullscreen, const char *title);

	// assets destroyed in destructor
	virtual ~Game1();

	// update / draw called each frame automaticly
	virtual void Update(float deltaTime);
	virtual void Draw();

protected:

	SpriteBatch	        *m_spritebatch;

	Input				*input;

	//Texture*	        t;
	Texture*	        t1;
	Texture*	        t2;
	Texture*            t3;

	Graph*		        graph;
	vec3		        mousePosition;

	std::list<Node*>    outPath;
	std::list<Node*>	potEndNodes;
	Node*				node1;

	Pathfinder*			pathfinder;
};

#endif