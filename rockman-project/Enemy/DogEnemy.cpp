#include "stdafx.h"
#include "DogEnemy.h"

void DogEnemy::Init()
{
	Enemy::Init();
	type = Types::Dog;
	speed = 100.f;
	hp = 40;
	animator.Play("animations/dog.csv");
}

void DogEnemy::Reset()
{
	Enemy::Reset();
}

void DogEnemy::UpdateBehavior(float dt)
{
}
