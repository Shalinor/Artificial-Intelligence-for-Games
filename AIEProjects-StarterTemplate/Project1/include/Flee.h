#pragma once

#include "Input.h"

#include "Agent.h"
#include "IBehaviour.h"

class Flee : public IBehaviour
{
public:
	Flee();
	~Flee();
	virtual void Update(Agent* agent_, float deltaTime_);
};