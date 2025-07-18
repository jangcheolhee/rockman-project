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

void BasicPlayer::SetAni(const std::string& ani)
{
	this->ani = ani;
	animator.Play(this->ani);
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

	animator.AddEvent("WoodMan1", 20,
		[this]()
		{

			SCENE_MGR.ChangeScene(SceneIds::Game);
		}
	);

	animator.AddEvent("Equip", 12,
		[this]()
		{

			speed = -100;
		}
	);
	animator.AddEvent("Equip", 15,
		[this]()
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
	
	
	if (name == "Player")
	{
		animator.Play("animations/titleIdle.csv");
		
	}
	else if(name == "Opening")
	{
		animator.Play("animations/opening.csv");
		
	}
	else if (name == "Boss")
	{
		animator.Play("animations/woodMan1.csv");
	}

	
}

void BasicPlayer::Update(float dt)
{
	if (name == "Player")
	{
		if (speed != 0)
		{
			sf::Vector2f pos = GetPosition();
			pos.y = pos.y + speed * dt;
			SetPosition(pos);
		}
		
		
	}
	animator.Update(dt);
		
}

void BasicPlayer::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}