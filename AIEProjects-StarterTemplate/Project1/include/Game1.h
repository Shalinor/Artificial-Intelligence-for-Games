
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

using glm::vec2;

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
	Texture*			defaultTexture;
	Texture*	        startTexture;
	Texture*	        endTexture;
	Texture*            traversedTexture;
	Texture*			pathTexture;

	Graph*		        graph;
	vec3		        mousePosition;

	std::list<Node*>    outPath;
	std::list<Node*>	potEndNodes;
	Node*				startNode;

	Pathfinder*			pathfinder;
	bool				newSearch;
	bool				continueSearch;
	bool				spaceReleased;
	bool				rReleased;
	bool				pReleased;
	bool				sReleased;
	bool				eReleased;
	bool				iReleased;
	bool				cReleased;
	bool				dReleased;
	bool				oneReleased;
	bool				twoReleased;
	bool				threeReleased;

	bool				mouseLeftReleased;
	//bool				mouseRightReleased;

	int					gridSize;
	float				gridSpacing;

	void				ResetSearches();


	//Menu
	Font*				menuFont;
	char*				menuText;
	vec2				menuPos;

	bool				displayIDs;
	bool				displayCosts;
	bool				displayDirections;

	void				LoadMenu();
};

#endif