#pragma once

#include "IBehaviour.h"

class Seek : IBehaviour
{
public:
	//Assuming this should be private but meh for now...
	shared_ptr<vec2>	targetPosition;

	virtual void Update(Agent* agent_);
};