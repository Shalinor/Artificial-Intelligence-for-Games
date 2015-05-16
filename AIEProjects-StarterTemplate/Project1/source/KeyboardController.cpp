#include "KeyboardController.h"

KeyboardController::KeyboardController()
{
	input = Input::GetSingleton();
}

KeyboardController::~KeyboardController()
{

}

void KeyboardController::Update(Agent* agent_, float deltaTime_)
{
	vec2 acceleration = {0.0f, 0.0f};

	if (input->IsKeyDown(GLFW_KEY_W))
	{
		acceleration.y = -1.0f;
	}

	if (input->IsKeyDown(GLFW_KEY_S))
	{
		acceleration.y = 1.0f;
	}

	if (input->IsKeyDown(GLFW_KEY_A))
	{
		acceleration.x = -1.0f;
	}

	if (input->IsKeyDown(GLFW_KEY_D))
	{
		acceleration.x = 1.0f;
	}

	agent_->SetAcceleration(acceleration);
}