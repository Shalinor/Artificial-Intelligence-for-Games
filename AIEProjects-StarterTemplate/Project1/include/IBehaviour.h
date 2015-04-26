#pragma once

//#include "Agent.h"
class Agent;

class IBehaviour
{
public:
				IBehaviour();
				~IBehaviour();

	virtual void Update(Agent* agent_, float deltaTime_) = 0;
};