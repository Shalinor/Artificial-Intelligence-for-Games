#include "Flee.h"

Flee::Flee() : IBehaviour(Type::FleeBehaviour)
{

}

Flee::~Flee()
{

}

void Flee::Update(Agent* agent_, float deltaTime_)
{
	//Flee from target

	if (agent_->GetAgentPosition() != agent_->GetTargetPosition())
	{
		//Calculate vector away from target - Note the order of subtraction is swapped
		vec2	distance = (agent_->GetAgentPosition() - agent_->GetTargetPosition());// *agent_->GetMaxSpeed();

		//Calculate magnitude in order to normalise
		float	magnitude = sqrtf(((distance.x * distance.x) + (distance.y * distance.y)));

		//Normalise vector & multiply by agent's max speed
		vec2	force = (distance / magnitude) * agent_->GetMaxSpeed();

		//Set the force for the agent
		agent_->AddForce(force);
	}
}
