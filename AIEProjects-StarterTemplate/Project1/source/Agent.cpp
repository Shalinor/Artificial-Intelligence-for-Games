#include "Agent.h"

Agent::Agent(std::shared_ptr<Texture> texture_)
{
	behaviours.push_back(make_shared<KeyboardController>());
}

Agent::~Agent()
{

}

void Agent::Update(float deltaTime_)
{
	//TODO: Sensing Calculations
	//TODO: Thinking Calculations
	//			Add or remove behaviours from the behaviours list

	//Acting
	for (auto iterator = behaviours.begin(); iterator != behaviours.end(); ++iterator)
	{
		(*iterator)->Update(this, deltaTime_);
	}

	//TODO: Physics stuff with force, acceleration, velocity, etc...
}
