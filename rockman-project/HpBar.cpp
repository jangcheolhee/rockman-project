#include "stdafx.h"
#include "HpBar.h"

HpBar::HpBar(const std::string& name)
	: GameObject(name)
{
}

void HpBar::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void HpBar::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void HpBar::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void HpBar::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void HpBar::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void HpBar::SetHpBar(int idx)
{
	body.setTexture(TEXTURE_MGR.Get("graphics/energyBars.png"));
	body.setTextureRect({ 1 + (idx * 9),264,8,56});
}

void HpBar::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;
}

void HpBar::Release()
{
}

void HpBar::Reset()
{
	body.setTexture(TEXTURE_MGR.Get("graphics/energyBars.png"));
	body.setTextureRect({ 1,264,8,56 });
	body.setPosition({ 50.0f,50.0f });
	body.setScale({ 2.0f,2.0f });

}

void HpBar::Update(float dt)
{
}

void HpBar::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}