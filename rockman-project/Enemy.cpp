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

		animator.Play("animations/bat.csv");
		break;
	case Enemy::Types::Rabbit:
		break;
	case Enemy::Types::Total:
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
	switch (type)
	{
	case Enemy::Types::Bat:

		direction = Utils::GetNormal(player->GetPosition() - GetPosition());
		if (Utils::Magnitude(player->GetPosition() - GetPosition()) > 50 && Utils::Magnitude(player->GetPosition() - GetPosition()) < 200)
		{

			SetRotation(Utils::Angle(direction));
			SetPosition(GetPosition() + direction * speed * dt);

		}
		break;
	case Enemy::Types::Rabbit:
		break;
	case Enemy::Types::Total:
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
		
		
		break;
	

	}
}
