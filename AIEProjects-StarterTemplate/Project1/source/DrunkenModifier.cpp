#include "DrunkenModifier.h"
#include <iostream>

DrunkenModifier::DrunkenModifier()
{
	accumulatedTime = 0.0f;
}

DrunkenModifier::~DrunkenModifier()
{

}

void DrunkenModifier::Update(Agent* agent_, float deltaTime_)
{
	accumulatedTime += deltaTime_;

	agent_->AddForce(sinf(100 * accumulatedTime * (3.141592f / 180.f)));// sinf(accumulatedTime));
	//Had guidance from Jarrod Hamilton on this one - I just needed the multipliers :)
}



//void DrunkenModifier::Update(Agent *agent, float deltaTime){
//	agent->acceleration = Vector2(1, 1);
//	agent->direction = sin(100 * (float)glfwGetTime() * (M_PI / 180));
//
//	std::cout << agent->direction << std::endl;
//}

