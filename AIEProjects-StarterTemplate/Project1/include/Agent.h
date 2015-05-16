#pragma once

#define GLM_FORCE_PURE

#include "glfw3.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <memory>
#include <list>

#include "Texture.h"
#include "SpriteBatch.h"

#include "IBehaviour.h"
#include "KeyboardController.h"
#include "DrunkenModifier.h"
#include "Seek.h"
#include "Flee.h"
#include "Wander.h"

using glm::vec2;
using std::shared_ptr;
using std::make_shared;

class Agent
{
public:
										Agent(std::shared_ptr<Texture> texture_);
										~Agent();

	virtual void						Update(float deltaTime_);
	virtual void						Draw(SpriteBatch* spriteBatch_);

	void								SetAcceleration(vec2 acceleration_);
	void								AddForce(float force_);
	void								AddForce(vec2 force_);
	void								SetTargetPosition(vec2 targetPosition_) { targetPosition = targetPosition_; }

	float								GetMaxSpeed() { return maxSpeed; }
	float								GetHeading() { return heading; }
	vec2/*std::shared_ptr<vec2>*/		GetTargetPosition() { return targetPosition; }
	vec2								GetAgentPosition() { return position; }
	vec2								GetVelocity() { return velocity; }
	vec2								GetNormalisedVelocity();

private:
	std::shared_ptr<Texture>			texture;

	std::list<shared_ptr<IBehaviour>>	behaviours;

	float								maxSpeed;
	float								heading;

	vec2								position;
	vec2								velocity;
	vec2								acceleration;


	vec2/*shared_ptr<vec2>*/			targetPosition;
};

/*
#include <memory>

//Declaration
shared_ptr<CLASS_NAME> node;

//"New" call
node = make_shared<CLASS_NAME>(any params here);
*/