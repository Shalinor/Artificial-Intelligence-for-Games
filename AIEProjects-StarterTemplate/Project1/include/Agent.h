#pragma once

#include "glfw3.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <memory>
#include <list>

#include "Texture.h"
#include "SpriteBatch.h"

#include "IBehaviour.h"
#include "KeyboardController.h"

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

private:
	void	AddForce(float force_);

	std::shared_ptr<Texture>			texture;

	std::list<shared_ptr<IBehaviour>>	behaviours;

	vec2								position;
	vec2								velocity;
	vec2								acceleration;
	vec2								force;
};

/*
#include <memory>

//Declaration
shared_ptr<CLASS_NAME> node;

//"New" call
node = make_shared<CLASS_NAME>(any params here);
*/