#include "stdafx.h"
#include "BasicPlayer.h"
BasicPlayer::BasicPlayer(const std::string& name)
	: GameObject(name)
{
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
}

void BasicPlayer::Release()
{
}

void BasicPlayer::Reset()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;
	
	if (name == "Player")
	{
		animator.Play("animations/opening.csv");
	}
	else 
	{
		animator.Play("animations/opening.csv");
		SetScale({ 4.f,4.f });
	}
	
}

void BasicPlayer::Update(float dt)
{
	animator.Update(dt);
	
}

void BasicPlayer::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}