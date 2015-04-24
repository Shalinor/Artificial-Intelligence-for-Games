#include "KeyboardController.h"

KeyboardController::KeyboardController()
{
	input = Input::GetSingleton();
}

void KeyboardController::Update(Agent* agent_, float deltaTime_)
{
	if (input->WasKeyPressed(GLFW_KEY_W))
	{

	}

}