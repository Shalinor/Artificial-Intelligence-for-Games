#pragma once
#include "Input.h"

#include "IBehaviour.h"

class KeyboardController :	public IBehaviour
{
public:
	KeyboardController();

	virtual void Update(Agent* agent_, float deltaTime_);

private:
	Input*	input;
};

