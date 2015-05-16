#include "Wander.h"

#include <iostream>

Wander::Wander()
{
	/*
	 *	Larger radius / lower distance == more turns
	 *	Smaller radius / higher distance == less turns
	 *	Larger jitter == more erratic turns
	 */

	radius = 250.f;
	distance = 100.f;
	jitter = 5.f;	//vec2? +/- 2 or so???  <-Jason in the Tutorial
}

Wander::~Wander()
{

}

void Wander::Update(Agent* agent_, float deltaTime_)
{
	vec2 tempTarget, displacement = { 0.f, 0.f };

	//Psuedo'd from http://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-wander--gamedev-1624
	//Calculate the circle center (normalized agent velocity)
	vec2 circleCenter = agent_->GetNormalisedVelocity();

	//Scale circle by distance
	circleCenter *= distance;
	
	
	//Calculate the displacement force
	float displacementMagnitude = radius * sqrtf(2.f);



	//Randomly change the vector direction by making it change its current angle
	float randomRadians = (rand() % 360) * (3.141592f / 180);

	displacement.x = cosf(randomRadians) * displacementMagnitude;// radius;
	displacement.y = sinf(randomRadians) * displacementMagnitude;// radius;


	//Change wanderAngle just a bit so it won't have the same value in the next game frame
	//not implemented at this point

	//Finally calculate and return the wander force
	tempTarget = circleCenter + displacement + agent_->GetAgentPosition();

	agent_->SetTargetPosition(tempTarget);

}

/*
private function wander() :Vector3D {
	// Calculate the circle center
	var circleCenter :Vector3D;
	circleCenter = velocity.clone();
	circleCenter.normalize();
	circleCenter.scaleBy(CIRCLE_DISTANCE);
	//
	// Calculate the displacement force
	var displacement :Vector3D;
	displacement = new Vector3D(0, -1);
	displacement.scaleBy(CIRCLE_RADIUS);
	//
	// Randomly change the vector direction
	// by making it change its current angle
	setAngle(displacement, wanderAngle);
	//
	// Change wanderAngle just a bit, so it
	// won't have the same value in the
	// next game frame.
	wanderAngle += Math.random() * ANGLE_CHANGE - ANGLE_CHANGE * .5;
	//
	// Finally calculate and return the wander force
	var wanderForce :Vector3D;
	wanderForce = circleCenter.add(displacement);
	return wanderForce;
}

public function setAngle(vector :Vector3D, value:Number):void {
	var len :Number = vector.length;
	vector.x = Math.cos(value) * len;
	vector.y = Math.sin(value) * len;
}
*/

/*{
	vec2 tempTarget;

	//Determine Wander target
	//Find random target on the edge of the sphere within a set "radius" of the agent
////////	tempTarget = glm::circularRand(radius);
	vec2 velocity = agent_->GetVelocity();

	if (velocity.x != 0.f || velocity.y != 0.f)
	{
		float randomRadians = (rand() % 360) * (3.141592f / 180);

		tempTarget.x = cosf(agent_->GetHeading() + randomRadians) + radius;
		tempTarget.y = sinf(agent_->GetHeading() + randomRadians) + radius;


		//tempTarget.x = ((velocity.x * cosf(randomRadians)) + (velocity.y * sinf(randomRadians)));
		//tempTarget.y = ((-velocity.x * sinf(randomRadians)) + (velocity.y * cosf(randomRadians)));


		//Add a randomised vector to the target with a magnitude specified by a "jitter" amount
		//(x cos alpha + y sin alpha, -x sin alpha + y cos alpha)
		randomRadians = (rand() % 360) * (3.141592f / 180);
		float targetHeading = atan2f(tempTarget.y, tempTarget.x) + 3.141592f / 2.0f;

		vec2 randomVector;
	//	randomVector.x = ((tempTarget.x * cosf(randomRadians)) + (tempTarget.y * sinf(randomRadians)));
//		randomVector.y = ((-tempTarget.x * sinf(randomRadians)) + (tempTarget.y * cosf(randomRadians)));
		randomVector.x = cosf(targetHeading + randomRadians) + jitter;
		randomVector.y = sinf(targetHeading + randomRadians) + jitter;

		tempTarget += randomVector;	//Add the randomised vector

		//Bring the target back to the radius by normalising it and scaling by the radius
		float magnitude = sqrtf(((tempTarget.x * tempTarget.x) + (tempTarget.y * tempTarget.y)));
		//Calculate magnitude in order to normalise
		tempTarget = (tempTarget / magnitude);	//Normalise vector
		tempTarget *= radius;					//Scale by radius


		//Add the agent's heading (normalised velocity??), multiplied by the "distance", to the target
		vec2 normalisedVelocity = agent_->GetNormalisedVelocity();
		tempTarget += normalisedVelocity * distance;

		agent_->SetTargetPosition(tempTarget);
	}
}*/

/*{
	vec2 tempTarget;

	//Determine Wander target
	//Find random target on the edge of the sphere within a set "radius" of the agent
	tempTarget = glm::circularRand(radius);

	//	std::cout << "tt: " << tempTarget.x << ", " << tempTarget.y;

	//Add a randomised vector to the target with a magnitude specified by a "jitter" amount
	//(x cos alpha + y sin alpha, -x sin alpha + y cos alpha)
	float randomRadians = (rand() % 360) * (3.141592f / 180);

	//	std::cout << " rr: " << randomRadians;

	vec2 randomVector;
	randomVector.x = ((tempTarget.x * cosf(randomRadians)) + (tempTarget.y * sinf(randomRadians)));
	randomVector.y = ((-tempTarget.x * sinf(randomRadians)) + (tempTarget.y * cosf(randomRadians)));

	//	std::cout << " rv: " << randomVector.x << ", " << randomVector.y;

	tempTarget += randomVector;	//Add the randomised vector

	//	std::cout << " tt+rv: " << tempTarget.x << ", " << tempTarget.y;

	//Bring the target back to the radius by normalising it and scaling by the radius
	float magnitude = sqrtf(((tempTarget.x * tempTarget.x) + (tempTarget.y * tempTarget.y)));
	//Calculate magnitude in order to normalise

	//	std::cout << " m: " << magnitude;

	tempTarget = (tempTarget / magnitude);	//Normalise vector

	//	std::cout << " tt/m: " << tempTarget.x << ", " << tempTarget.y;

	tempTarget *= radius;					//Scale by radius

	//	std::cout << " tt*r: " << tempTarget.x << ", " << tempTarget.y;

	//Add the agent's heading (normalised velocity??), multiplied by the "distance", to the target
	vec2 normalisedVelocity = agent_->GetNormalisedVelocity();

	//	std::cout << " nv: " << normalisedVelocity.x << ", " << normalisedVelocity.y;

	tempTarget += normalisedVelocity * distance;

	//	std::cout << " tt+nv*d: " << tempTarget.x << ", " << tempTarget.y;

	//	std::cout << "Prev Target: " << agent_->GetTargetPosition().x << ", " << agent_->GetTargetPosition().y << "\n";

	agent_->SetTargetPosition(tempTarget);

	//	std::cout << "Post Target: " << agent_->GetTargetPosition().x << ", " << agent_->GetTargetPosition().y << "\n";
}*/