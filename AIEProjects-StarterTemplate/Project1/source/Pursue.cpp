#include "Pursue.h"

Pursue::Pursue() : IBehaviour(Type::PursueBehaviour)
{

}

Pursue::~Pursue()
{

}

void Pursue::Update(Agent* agent_, float deltaTime_)
{
	//Pursue towards target

//	if (agent_->GetAgentPosition() != agent_->GetTargetPosition())
//	{
		//Calculate vector to target
		vec2	distance = ((agent_->GetTargetPosition() + agent_->GetTargetVelocity()) - agent_->GetAgentPosition());// *agent_->GetMaxSpeed();

		//Calculate magnitude in order to normalise
		float	magnitude = sqrtf(((distance.x * distance.x) + (distance.y * distance.y)));

		//Normalise vector & multiply by agent's max speed
		vec2	force = ((distance / magnitude) * agent_->GetMaxSpeed()) - agent_->GetVelocity();

		//Set the force for the agent
		agent_->AddForce(force);
//	}
}
