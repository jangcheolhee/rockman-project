#include "stdafx.h"
#include "Bullet.h"
#include "SceneGame.h"
#include "Enemy.h"
Bullet::Bullet(const std::string& name)
	: GameObject(name)
{
}

void Bullet::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Bullet::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Bullet::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Bullet::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Bullet::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Bullet::Fire(const sf::Vector2f& pos, const sf::Vector2f& dir, float s, int d)
{
	SetPosition(pos);
	direction = dir;
	speed = s;
	damage = d;

	SetRotation(Utils::Angle(direction));
}

void Bullet::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
}

void Bullet::Release()
{
}

void Bullet::Reset()
{
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	body.setTexture(TEXTURE_MGR.Get(texId), true);
	SetOrigin(Origins::ML);
	SetPosition({ 0.f,0.f });
	SetRotation(0.f);
	SetScale({ 0.2f,0.4f });

	direction = { 0.f,0.f };
	speed = 1000.f;
	damage = 0;
	
}

void Bullet::Update(float dt)
{
	SetPosition(position + direction * speed * dt);
	hitBox.UpdateTransform(body, GetLocalBounds());
	const auto& list = sceneGame->GetEnemies();
	for (auto enemy : list)
	{
		if (Utils::CheckCollision(hitBox.rect, enemy->GetHitBox().rect))
		{
			SetActive(false);
			enemy->OnDamage(damage);
			break;
		}
	}
	if (position.x < 0 || position.x > 4000)
	{
		SetActive(false);
	}
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}