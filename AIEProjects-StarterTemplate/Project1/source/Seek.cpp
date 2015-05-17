#include "Seek.h"

Seek::Seek() : IBehaviour(Type::SeekBehaviour)
{

}

Seek::~Seek()
{

}

void Seek::Update(Agent* agent_, float deltaTime_)
{
	//Seek towards target

	if (agent_->GetAgentPosition() != agent_->GetTargetPosition())
	{
		//Calculate vector to target
		vec2	distance = (agent_->GetTargetPosition() - agent_->GetAgentPosition());// *agent_->GetMaxSpeed();

		//Calculate magnitude in order to normalise
		float	magnitude = sqrtf(((distance.x * distance.x) + (distance.y * distance.y)));

		//Normalise vector & multiply by agent's max speed
		vec2	force = (distance / magnitude) * agent_->GetMaxSpeed();

		//Set the force for the agent
		agent_->AddForce(force);
	}
}
