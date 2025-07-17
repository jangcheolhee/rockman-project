#include "stdafx.h"
#include "Enemy.h"
#include "SceneGame.h"
#include "AniPlayer.h"
Enemy::Enemy(const std::string& name)
	: GameObject(name)
{
}

void Enemy::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Enemy::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Enemy::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Enemy::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Enemy::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Enemy::OnDamage(int damage)
{
	if (!isMove) damage = 0;
	hp = Utils::Clamp(hp - damage, 0, 100);
	if (hp == 0)
	{
		SetActive(false);
	}
}

void Enemy::Init()
{
	animator.SetTarget(&body);

	//animator.AddEvent("Bat", 0,
	//	[]()
	//	{
	//		std::cout << "!!" << std::endl;

	//	}
	//);

	//animator.AddEvent("Idle", 0,
	//	[]()
	//	{
	//		std::cout << "??" << std::endl;
	//	}
	//);
}

void Enemy::Release()
{
}

void Enemy::Reset()
{
	if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Game)
	{
		sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene(); //�ٿ� ĳ���� 
	}
	else
	{
		sceneGame = nullptr;
	}
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	switch (type)
	{
	case Enemy::Types::Bat:
		SetScale({ 1.f,1.f });
		animator.Play("animations/bat.csv");
		isMove = false;
		break;
	case Enemy::Types::Rabbit:
		
		animator.Play("animations/rabbit.csv");
		isMove = true;
		isGrounded = false;
		break;
	case Enemy::Types::Count:
		break;
	default:
		break;
	}
	player = (AniPlayer*)SCENE_MGR.GetCurrentScene()->FindGameObject("AniPlayer");

	
	
	SetOrigin(Origins::BC);
}

void Enemy::Update(float dt)
{
	animator.Update(dt);
	float s = speed;
	switch (type)
	{
	case Enemy::Types::Bat:

		direction = Utils::GetNormal(player->GetPosition() - GetPosition());
		
		if (Utils::Magnitude(player->GetPosition() - GetPosition()) >10 && Utils::Magnitude(player->GetPosition() - GetPosition()) < 100)
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
			player->OnDamage(2);
			
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
		break;
	case Enemy::Types::Rabbit:

		
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
		break;
	
	default:
		break;
	}

	hitBox.UpdateTransform(body, GetLocalBounds());
	
}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}

void Enemy::SetType(Types type)
{
	this->type = type;
	switch (this->type)
	{
	case Types::Bat:
		hp = 100;
		speed = 50.f;
		
		break;
	case Types::Rabbit:
		hp = 100;
		speed = 50.f;
		moveInetrval = 3.0f;
		break;

	}
}
