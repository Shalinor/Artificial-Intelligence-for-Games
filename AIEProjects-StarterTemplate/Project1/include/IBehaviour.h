#pragma once

#include "Agent.h"

class IBehaviour
{
public:
	virtual void Update(Agent* agent_, float deltaTime_) = 0;
};