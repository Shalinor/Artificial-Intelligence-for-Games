
/*-----------------------------------------------------------------------------
Author:			
Description:	
-----------------------------------------------------------------------------*/
//#ifndef GAME1_H
//#define GAME1_H
#pragma once

#include <list>

#include "Application.h"
#include <memory>

class SpriteBatch;
class Texture;		//<- I don't like this method, I know it avoids polluting namespace, but meh...
class Input;

using glm::vec2;

using std::shared_ptr;
using std::make_shared;

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

	SpriteBatch*		m_spritebatch;	//Needs <?> to be a std pointer due to classes design - Destroy, etc??

	Input				*input;

	//Texture*	        t;
	Texture*			defaultTexture;
	
	//Menu
	Font*				menuFont;
	char*				menuText;
	vec2				menuPos;

	void				LoadMenu();
};

//#endif