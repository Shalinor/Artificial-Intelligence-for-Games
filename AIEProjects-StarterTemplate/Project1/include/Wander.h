#pragma once

#include "Input.h"

#include "Agent.h"
#include "IBehaviour.h"

class Wander : public IBehaviour
{
public:
	Wander();
	~Wander();
	virtual void Update(Agent* agent_, float deltaTime_);

private:
	float radius;
	float distance;
	float jitter;
};