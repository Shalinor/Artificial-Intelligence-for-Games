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

using glm::vec2;
using std::shared_ptr;
using std::make_shared;

class Agent
{
public:
			Agent(std::shared_ptr<Texture> texture_);
			~Agent();

	virtual void	Update(float deltaTime_);
	virtual void	Draw(SpriteBatch* spriteBatch_);

	void			SetAcceleration(vec2 acceleration_);	//AddForce
	void			AddForce(float force_);

private:
	std::shared_ptr<Texture>			texture;

	std::list<shared_ptr<IBehaviour>>	behaviours;

	float								maxSpeed;
	float								heading;

	vec2								position;
	vec2								velocity;
	vec2								acceleration;
};

/*
#include <memory>

//Declaration
shared_ptr<CLASS_NAME> node;

//"New" call
node = make_shared<CLASS_NAME>(any params here);
*/