#include "KeyboardController.h"

KeyboardController::KeyboardController()
{
	input = Input::GetSingleton();
}

void KeyboardController::Update(Agent* agent_, float deltaTime_)
{
	/*
	Matrix3x3	translationMatrix = Matrix3x3::SetupTranslation(Vector2(
												(cosf(playerAngle) * movement.y),
												(sinf(playerAngle) * movement.y)));
	*/

	float	velocity = 0.f;	//Forward/backward
	float	rotation = 0.f;	//Turn left/right - 1 Radian == 0.0174532925

	if (input->IsKeyDown(GLFW_KEY_W))
	{
		velocity -= 10.f;
	}

	if (input->IsKeyDown(GLFW_KEY_S))
	{
		velocity += 10.f;
	}

	if (input->IsKeyDown(GLFW_KEY_A))
	{
		rotation -= 0.174532925f;	//10 Radians - magic number
	}

	if (input->IsKeyDown(GLFW_KEY_D))
	{
		rotation += 0.174532925f;	//10 Radians - magic number
	}

	glm::rotate

	vec2	force = vec2((cosf(agent_->GetHeading()) * velocity), ());

}