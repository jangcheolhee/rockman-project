#include "stdafx.h"
#include "OstrichEnemy.h"
#include "AniPlayer.h"
#include "SceneGame.h"

void OstrichEnemy::Init()
{
	Enemy::Init();
	type = Types::Ostrich;
	speed = 100.f;
	hp = 20;
	animator.Play("animations/ostrich.csv");
	direction = { -1.f, 0.f };
}

void OstrichEnemy::Reset()
{
	Enemy::Reset();
}

void OstrichEnemy::UpdateBehavior(float dt)
{
	if (!isGrounded)
	{
		velocity += gravity * dt;
	}

	velocity.x = -speed;
	position += velocity * dt;
	position.x = Utils::Clamp(position.x, sceneGame->GetZoneBounds().left + GetLocalBounds().width / 2, sceneGame->GetZoneBounds().left + sceneGame->GetZoneBounds().width - GetLocalBounds().width / 2);
	if (sceneGame->FloorCheck(GetPosition().x, GetPosition().y + 1))
	{
		velocity.y = 0.f;
		position.y -= 0.1f;
		isGrounded = true;
	}

	if (Utils::Magnitude(player->GetPosition() - GetPosition()) < 10)
	{
		player->OnDamage(4);

	}else if (Utils::Magnitude(player->GetPosition() - GetPosition()) < 30)
	{
		velocity.y = -150.f;
		

	}
	isGrounded = false;
	SetPosition(position);
}
