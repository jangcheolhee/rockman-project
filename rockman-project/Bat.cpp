#include "stdafx.h"
#include "Bat.h"
#include "SceneGame.h"
Bat::Bat(const std::string& name)
	: GameObject(name)
{
}

void Bat::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Bat::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Bat::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Bat::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Bat::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Bat::OnDamage(int damage)
{
	hp = Utils::Clamp(hp - damage, 0, 100);
	if (hp == 0)
	{
		SetActive(false);
	}
}

void Bat::Init()
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

void Bat::Release()
{
}

void Bat::Reset()
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

	animator.Play("animations/bat.csv");
	hp = 100;
	SetOrigin(Origins::BC);
}

void Bat::Update(float dt)
{
	animator.Update(dt);

	hitBox.UpdateTransform(body, GetLocalBounds());
}

void Bat::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}