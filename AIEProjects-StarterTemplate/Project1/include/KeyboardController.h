#pragma once

/*
 *	KeyboardControler behaviour.
 *	Create a KeyboardControlerClass that inherits from IBehaviour.
 *	This should override the update function, and apply force to the
 *		agent passed into the update based on key press.
 */


#include "Input.h"

#include "Agent.h"
#include "IBehaviour.h"

class KeyboardController :	public IBehaviour
{
public:
	KeyboardController();
	~KeyboardController();

	virtual void Update(Agent* agent_, float deltaTime_);

private:
	Input*	input;
};

