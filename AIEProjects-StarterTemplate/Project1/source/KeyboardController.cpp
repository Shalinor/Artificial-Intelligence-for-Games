#include "KeyboardController.h"

KeyboardController::KeyboardController() : IBehaviour(Type::KeyboardControllerBehaviour)
{
	input = Input::GetSingleton();
}

KeyboardController::~KeyboardController()
{

}

void KeyboardController::Update(Agent* agent_, float deltaTime_)
{
	if (input->IsMouseButtonDown(0))												//If LMB clicked
	{
		agent_->SetTargetPosition(vec2(input->GetMouseX(), input->GetMouseY()));	//Set agent's target position
	}

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