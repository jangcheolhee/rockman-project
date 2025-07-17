#include "stdafx.h"
#include "BasicPlayer.h"
BasicPlayer::BasicPlayer(const std::string& name)
	: GameObject(name)
{
}

void BasicPlayer::changeAni()
{
	if (name == "Player")
	{
		animator.Play("animations/equip.csv");

	}
}

void BasicPlayer::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void BasicPlayer::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void BasicPlayer::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void BasicPlayer::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void BasicPlayer::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void BasicPlayer::Init()
{
	animator.SetTarget(&body);


	animator.AddEvent("Equip", 11,
		[]()
		{
			SCENE_MGR.ChangeScene(SceneIds::Stage);
		}
	);
}

void BasicPlayer::Release()
{
}

void BasicPlayer::Reset()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;
	SetScale({ 4.f,4.f });
	if (name == "Player")
	{
		animator.Play("animations/titleIdle.csv");
		
	}
	else 
	{
		animator.Play("animations/opening.csv");
		
	}
	speed = 0;
	
}

void BasicPlayer::Update(float dt)
{
	if (name == "Player")
	{
		if (speed != 0)
		{
			sf::Vector2f pos = GetPosition();
			pos.y = pos.y * speed * dt;
			SetPosition(pos);
		}
		
		
	}
	animator.Update(dt);
		
}

void BasicPlayer::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}