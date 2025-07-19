#include "stdafx.h"
#include "BatEnemy.h"
#include "AniPlayer.h"

void BatEnemy::Init()
{
	Enemy::Init();
	type = Types::Bat;
	speed = 100.f;
	hp = 8;
	animator.Play("animations/bat.csv");
}
void BatEnemy::Reset()
{
	Enemy::Reset();

}
void BatEnemy::UpdateBehavior(float dt)
{
	direction = Utils::GetNormal(player->GetPosition() - GetPosition());
	float s = speed;
	if (Utils::Magnitude(player->GetPosition() - GetPosition()) > 10 && Utils::Magnitude(player->GetPosition() - GetPosition()) < 100)
	{
		if (!isMove)
		{
			scale.y *= -1;
			animator.Play("animations/bat.csv");
		}
		isMove = true;

		SetScale({ 1.f, 1.f });


	}
	else if (Utils::Magnitude(player->GetPosition() - GetPosition()) < 10)
	{
		player->OnDamage(4);
		SetPosition({ position.x, position.y - 80 });

	}
	else
	{
		s = 0;
		if (!isMove)
		{

			animator.Play("animations/bat2.csv");

		}
		isMove = false;
	}
	SetPosition(GetPosition() + direction * s * dt);

}
