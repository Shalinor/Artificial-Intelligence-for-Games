#pragma once

#include "Input.h"

#include "Agent.h"
#include "IBehaviour.h"

class Pursue : public IBehaviour
{
public:
	Pursue();
	~Pursue();
	virtual void Update(Agent* agent_, float deltaTime_);
};