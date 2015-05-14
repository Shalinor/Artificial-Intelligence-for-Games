#include "Agent.h"

#include <iostream>

Agent::Agent(std::shared_ptr<Texture> texture_)
{
	texture = texture_;

	//Add behaviours to agent
	behaviours.push_back(make_shared<KeyboardController>());

	//Set default/initial values
	position = vec2(250.f, 200.f);
	velocity = vec2(0.f, 0.f);
	acceleration = vec2(10.f);
	force = vec2(0.f, 0.f);
	heading = vec2(1.f, 0.f);
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
	velocity += force * deltaTime_;
	position += velocity * deltaTime_;
	if (velocity != vec2(0.f))
		heading = glm::normalize(velocity);


}

void Agent::Draw(SpriteBatch* spriteBatch_)
{
	spriteBatch_->DrawSprite(texture.get(), position.x, position.y, 16.f, 16.f, atan2f(heading.y, heading.x));
}

void Agent::AddForce(vec2 force_)
{
	force = force_;
}

vec2 Agent::GetHeading()
{
	return heading;
}