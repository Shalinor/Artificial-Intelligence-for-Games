
/*-----------------------------------------------------------------------------
Author:			
Description:	
-----------------------------------------------------------------------------*/
#ifndef GAME1_H
#define GAME1_H

#include "Application.h"

class SpriteBatch;
class Texture;		//<- I don't like this method, I know it avoids polluting namespace, but meh...
class Graph;
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

	SpriteBatch	*m_spritebatch;

	Texture*	t;

	Graph*		graph;
	vec3		mousePosition;
	Input*		inputInstance;
};

#endif