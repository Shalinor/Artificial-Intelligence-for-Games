#pragma once

#include "Input.h"

#include "Agent.h"
#include "IBehaviour.h"

class Seek : public IBehaviour
{
public:
	Seek();
	~Seek();

	virtual void Update(Agent* agent_, float deltaTime_);
};