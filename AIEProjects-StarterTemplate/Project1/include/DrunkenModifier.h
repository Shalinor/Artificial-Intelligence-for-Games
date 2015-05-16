#pragma once

/*
 *	Create a DrunkenModifier behaviour.
 *	This should override the update function, this will need to calculate accumulative time.
 *	Apply a force to the agent, using the accumulative time passed into the sin function.
 *
 *	Lecture - make it move around in circles	Ended up being just really non-directional
 *
 *	This needs to be added to behaviour list "After" acceleration is determined...
 *
 */

#include "Input.h"

#include "Agent.h"
#include "IBehaviour.h"

class DrunkenModifier : public IBehaviour
{
public:
	DrunkenModifier();
	~DrunkenModifier();

	virtual void Update(Agent* agent_, float deltaTime_);

private:
	Input*	input;
	float	accumulatedTime;
};

