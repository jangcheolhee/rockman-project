#include "stdafx.h"
#include "RabbitEnemy.h"
#include "AniPlayer.h"
#include "SceneGame.h"

void RabbitEnemy::Init()
{
	Enemy::Init();
}

void RabbitEnemy::Reset()
{
	Enemy::Reset();
	animator.Play("animations/rabbit.csv");
	isGrounded = false;
	

}

void RabbitEnemy::UpdateBehavior(float dt)
{
	direction = Utils::GetNormal(player->GetPosition() - GetPosition());


	if (!isGrounded)
	{
		velocity += gravity * dt;
	}

	position += velocity * dt;
	position.x = Utils::Clamp(position.x, 70, 4000);
	if (sceneGame->FloorCheck(GetPosition().x, GetPosition().y + 1))
	{
		velocity.y = 0.f;
		velocity.x = 0.f;
		position.y -= 0.1f;
		isGrounded = true;
	}
	moveTimer += dt;
	if (moveTimer > moveInetrval)
	{
		if (direction.x < 0)
		{
			SetScale({ 1.f,1.f });
			velocity.x = -100.f;
		}
		else {
			SetScale({ -1.f,1.f });
			velocity.x = 100.f;
		}
		velocity.y = -150.f;
		isGrounded = false;
		moveTimer = 0;
	}
	SetPosition(position);

}
