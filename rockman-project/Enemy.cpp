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
		isAlive = false;
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

	
	player = (AniPlayer*)SCENE_MGR.GetCurrentScene()->FindGameObject("AniPlayer");

	SetActive(true);
	SetPosition(initPosition);
	SetScale({ 1.f,1.f });
	
	SetOrigin(Origins::BC);
	isAlive = true;

}

void Enemy::Update(float dt)
{
	animator.Update(dt);
	UpdateBehavior(dt);
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
