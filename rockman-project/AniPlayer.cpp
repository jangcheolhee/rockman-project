#include "stdafx.h"
#include "AniPlayer.h"
#include "Bullet.h"
#include "SceneGame.h"

AniPlayer::AniPlayer(const std::string& name)
	: GameObject(name)
{
}

void AniPlayer::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void AniPlayer::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void AniPlayer::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void AniPlayer::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		Utils::SetOrigin(body, originPreset);
	}
}

void AniPlayer::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = Utils::SetOrigin(body, originPreset);
}

void AniPlayer::Shoot()
{
	Bullet* bullet = nullptr;
	if (bulletPool.empty())
	{
		bullet = new Bullet();
		bullet->Init();
	}
	else
	{
		bullet = bulletPool.front();
		bulletPool.pop_front();
		bullet->SetActive(true);

	}

	bullet->Reset();
	sf::Vector2f pos = position + look * 10.f;
	pos.y -= 10;
	bullet->Fire(pos, look, 1000.f, 50);
	bulletList.push_back(bullet);
	sceneGame->AddGameObject(bullet);
}

void AniPlayer::Init()
{
	
	animator.SetTarget(&body);

	animator.AddEvent("Idle", 0,
		[]()
		{
			std::cout << "!!" << std::endl;
			
		}
	);

	animator.AddEvent("Idle", 0,
		[]()
		{
			std::cout << "??" << std::endl;
		}
	);
}

void AniPlayer::Release()
{
}

void AniPlayer::Reset()
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

	animator.Play("animations/idle.csv");
	
	SetOrigin(Origins::BC);

	for (Bullet* bullet : bulletList)
	{
		bullet->SetActive(false);
		bulletPool.push_back(bullet);
	}
	bulletList.clear();
	direction = { 0.f, 0.f };
	
	
}

void AniPlayer::Update(float dt)
{
	animator.Update(dt);
	
	float h = 0.f;
	
	
	if (isGrounded)
	{
		h = InputMgr::GetAxis(Axis::Horizontal);
		velocity.x = h * speed;

	}
	if (isGrounded && InputMgr::GetKeyDown(sf::Keyboard::Z))
	{
		isGrounded = false;
		
		velocity.y = -250.f;
		animator.Play("animations/jump.csv");
		
	}
	shootTimer += dt;
	if (InputMgr::GetKeyDown(sf::Keyboard::X) && shootTimer > shootInterval)
	{
		if (!isGrounded)
		{
			animator.Play("animations/shoot1.csv");
			
		}
		else
		{
			animator.Play("animations/shoot.csv");
		}
		shootTimer = 0.f;
		isShoot = true;
		Shoot();
		
	}
	if (!isGrounded)
	{
		velocity += gravity * dt;
	}
	position += velocity * dt;
	if (isGround)
	{
		velocity.y = 0.f;
		position.y -= 0.1f;
		isGrounded = true;
		isGround = false;
	}
	if (isLadder)
	{
	h:InputMgr::GetAxis(Axis::Vertical);
		velocity.y = h * speed;
	}
	SetPosition(position);

	if (h != 0.f)
	{
		SetScale(h > 0.f ? sf::Vector2f(1.0f, 1.0) : sf::Vector2f(- 1.f, 1.0f));
		look = (h > 0.f ? sf::Vector2f(1.0f, 0.f) : sf::Vector2f(-1.f, 0.f));
	}

	// Ani
	if (animator.GetCurrentClipId() == "Idle")
	{
		if (h != 0.f)
		{
			animator.Play("animations/run.csv");
		}
	}
	else if (animator.GetCurrentClipId() == "Run")
	{
		if (h == 0.f)
		{
			animator.Play("animations/idle.csv");
		}
	}
	else if (animator.GetCurrentClipId() == "Jump" && isGrounded)
	{
		if (h == 0.f)
		{
			animator.Play("animations/idle.csv");
		}
		else
		{
			animator.Play("animations/run.csv");
		}
	}
	else if (animator.GetCurrentClipId() == "Shoot1" &&  isGrounded)
	{
		
		if (h == 0.f)
		{
			animator.Play("animations/idle.csv");
		}
	
	
	}
	else if (animator.GetCurrentClipId() == "Shoot")
	{

		if (h == 0.f)
		{
			animator.Play("animations/idle.csv");
		}
		


	}
	
	hitbox.UpdateTransform(body, GetLocalBounds());
}

void AniPlayer::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitbox.Draw(window);
}
