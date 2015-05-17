#pragma once

//#include "Agent.h"
class Agent;

enum Type
{
	KeyboardControllerBehaviour,
	DrunkenModifierBehaviour,
	SeekBehaviour,
	FleeBehaviour,
	WanderBehaviour,
	PursueBehaviour,
	EvadeBehaviour,
	ArrivalBehaviour,
	AvoidBehaviour
};

class IBehaviour
{
public:
				IBehaviour(Type type_) { type = type_; }
				~IBehaviour();

	virtual void Update(Agent* agent_, float deltaTime_) = 0;

	Type		type;
};