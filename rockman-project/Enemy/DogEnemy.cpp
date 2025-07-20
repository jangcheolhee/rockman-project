#include "stdafx.h"
#include "DogEnemy.h"
#include "AniPlayer.h"

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
	if (Utils::Magnitude(player->GetPosition() - GetPosition()) < 10)
	{
		player->OnDamage(10);

	}
}
