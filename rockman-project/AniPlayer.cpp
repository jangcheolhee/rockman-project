#include "stdafx.h"
#include "AniPlayer.h"
#include "Bullet.h"
#include "SceneGame.h"
#include "HpBar.h"
#include <Particle.h>

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

void AniPlayer::Shoot() // 충돌 되었을시 발사 불가
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
	bullet->Fire(pos, look, 800.f, 50);
	bulletList.push_back(bullet);
	sceneGame->AddGameObject(bullet);
	idleShootTimer = 0;
}

void AniPlayer::Init()
{
	animator.SetTarget(&body);
}

void AniPlayer::Release()
{
}

void AniPlayer::Reset()
{
	if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Game)
		sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene();
	else
		sceneGame = nullptr;

	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	animator.Play("animations/idle.csv");
	SetOrigin(Origins::BC);

	state = State::Idle;
	
	hp = maxHp;
	look = { 1.f, 0.f };

	for (Bullet* bullet : bulletList)
	{
		bullet->SetActive(false);
		bulletPool.push_back(bullet);
	}
	bulletList.clear();

	direction = { 0.f, 0.f };
	velocity = { 0.f, 0.f };
	isGrounded = false;
	
	hpBar = (HpBar*)SCENE_MGR.GetCurrentScene()->FindGameObject("HpBar");
	hpBar->SetHpBar(maxHp - hp);

	damageTimer = 0.f;
	if (life == 0)
	{
		life = 3;
	}
	deadTimer = 0.f;
	ladder = false;
	isDead = false;
	SetActive(true);
}

void AniPlayer::Update(float dt)
{
	animator.Update(dt);
	damageTimer += dt;
	if (isDead)
	{
		deadTimer += dt;
		std::cout << deadTimer << std::endl;
		if (deadTimer > 1.5f) // 1초 후 씬 전환
		{
			
			SCENE_MGR.ChangeScene(SceneIds::Game);
			std::cout << 1232435;
		}
		
	}

	float h = InputMgr::GetAxis(Axis::Horizontal);
	float v = InputMgr::GetAxis(Axis::Vertical);
	

	// 이동 처리
	if (isGrounded)
		velocity.x = h * speed;

	// 점프 처리
	if (isGrounded && InputMgr::GetKeyDown(sf::Keyboard::Z))
	{
		isGrounded = false;
		velocity.y = -250.f;
		state = State::Jump;
		animator.Play("animations/jump.csv");
	}

	// 슈팅 처리
	shootTimer += dt;
	if (InputMgr::GetKeyDown(sf::Keyboard::X) && shootTimer > shootInterval)
	{
		isShoot = true;
		shootTimer = 0.f;
		Shoot();
	}
	auto it = bulletList.begin();
	while (it != bulletList.end())
	{
		if (!(*it)->GetActive())
		{
			bulletPool.push_back(*it);
			it = bulletList.erase(it);
		}
		else
		{
			it++;
		}
	}


	
	if (isGround)
	{
		if (isLadder)
		{
			state = State::Ladder;
			animator.Play("animations/ladder.csv");
			velocity.y = v * speed;
		}
		else
		{
			velocity.y = 0.f;
			position.y -= 0.1f;
		}

		isGround = false;
		isGrounded = true;
	}
	if (!isGrounded && !isLadder)
	{
		velocity += gravity * dt;
	}
	

	// 낙하 중인지 검사
	if (!sceneGame->FloorCheck(GetPosition().x, GetPosition().y + 1))
		isGrounded = false;


	// 위치 적용
	position += velocity * dt;
	position.x = Utils::Clamp(position.x, 150, 8000);

	SetPosition(position);

	// 방향 전환
	if (h != 0.f)
	{
		SetScale(h > 0.f ? sf::Vector2f(1.f, 1.f) : sf::Vector2f(-1.f, 1.f));
		look = (h > 0.f) ? sf::Vector2f(1.f, 0.f) : sf::Vector2f(-1.f, 0.f);
	}

	// 애니메이션 상태 전환
	
	switch (state)
	{
	case State::Idle:
		if (h != 0.f)
		{
			animator.Play("animations/run.csv");
			state = State::Run;
		}
		if (isShoot)
		{
			
			
			state = State::IdleShoot;
			
		}
		break;

	case State::Run:
		if (h == 0.f)
		{
			animator.Play("animations/idle.csv");
			state = State::Idle;
		}
		if (isShoot)
		{
			animator.Play("animations/shoot.csv");
			state = State::Shoot;
			isShoot = false;
		}
		break;

	case State::Shoot:
		if (h == 0.f)
		{
			animator.Play("animations/idle.csv");
			state = State::Idle;
		}
		break;

	case State::Jump:
		if (isGrounded)
		{
			if (h == 0.f)
			{
				animator.Play("animations/idle.csv");
				state = State::Idle;
			}
			else
			{
				animator.Play("animations/run.csv");
				state = State::Run;
			}
		}
		if (isShoot)
		{
			animator.Play("animations/shoot1.csv");
			isShoot = false;
			state = State::JumpShoot;
		}
		break;

	case State::JumpShoot:
		if (isGrounded)
		{
			if (h == 0.f)
			{
				animator.Play("animations/idle.csv");
				state = State::Idle;
			}
			else
			{
				animator.Play("animations/run.csv");
				state = State::Run;
			}
		}
		break;

	case State::Hurt:
	{
		sf::Color color = body.getColor();
		color.a =  100; // 보였다 안보였다
		body.setColor(color);
		if(damageTimer >1)
		{
			
			color.a = 255;
			body.setColor(color);
			animator.Play("animations/idle.csv");
			state = State::Idle;
		}
	}

		break;
	case State::Ladder:
		if (!isLadder)
		{
			if (h == 0.f)
			{
				animator.Play("animations/idle.csv");
				state = State::Idle;
				
			}
			else
			{
				animator.Play("animations/run.csv");
				state = State::Run;
			}
		}
		break;
	case State::IdleShoot:

		idleShootTimer += dt;
		if (idleShootTimer > 0.3)
		{
			if (h == 0.f)
			{
				animator.Play("animations/idle.csv");
				state = State::Idle;
			}
			else
			{
				animator.Play("animations/run.csv");
				state = State::Run;
			}
		}
		else
		{
			isShoot = false;
			body.setTexture(TEXTURE_MGR.Get("graphics/megaman_sprite.png"));
			body.setTextureRect({ 175,31, 26, 25 });
		}
		break;

	default:
		break;
	}

	hitbox.UpdateTransform(body, GetLocalBounds());
}

void AniPlayer::OnDamage(int damage)
{
	if (isDamage)
	{
		if (damageTimer > 1)
		{
			state = State::Hurt;
			damageTimer = 0;

			isGrounded = false;
			velocity.y += -80.f;
			velocity.x *= -1;
			animator.Play("animations/jump.csv");

			hp = Utils::Clamp(hp - damage, 0, 28);
			hpBar->SetHpBar(maxHp - hp);
			if (hp == 0)
			{
				life -= 1;

				if (life != 0)
				{
					isDead = true;
					deadTimer = 0.f;
					
					// 죽는 장면 추가
					const int directionCount = 10;
					

					float angleStep = 360.f / directionCount;

					
						for (int i = 0; i < directionCount; ++i)
						{
							float angle = angleStep * i;
							float rad = Utils::DegreeToRadian(angle);
							sf::Vector2f dir(cos(rad), sin(rad));

							// 속도를 천천히 (예: * 50.f)
							Particle* p = new Particle(position, dir * 50.f);
							p->Init();
							p->Reset();
							sceneGame->AddGameObject(p);
						}
					
					
					//SCENE_MGR.ChangeScene(SceneIds::Game);
				}
				else
				{
					
					SCENE_MGR.ChangeScene(SceneIds::Ending);
				}
			}
		}
	}

}

void AniPlayer::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitbox.Draw(window);
}