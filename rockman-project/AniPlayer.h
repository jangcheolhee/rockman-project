#pragma once
#include "Animator.h"
#include "HitBox.h"


class SceneGame;
class Bullet;
class HpBar;

class AniPlayer : public GameObject
{
public:
	enum class State
	{
		Default = -1,
		Idle,
		
		Run,
		Hurt,
		Shoot,
		Jump,
		JumpShoot,
		Ladder,
		IdleShoot,
		Count,
	};
protected:
	HpBar* hpBar;
	sf::Sprite body;
	Animator animator;
	State state;
	sf::Vector2f gravity = { 0.f, 500.f };
	sf::Vector2f velocity = { 0.f, 0.f };
	bool isGrounded = false;
	bool isGround = false;
	bool isLadder = false;
	bool isShoot = false;
	bool ladder = false;

	float speed = 100.f;
	HitBox hitbox;
	SceneGame* sceneGame = nullptr;
	sf::Vector2f direction;
	sf::Vector2f look;

	std::list <Bullet*> bulletList;
	std::list <Bullet*> bulletPool;

	float shootInterval = 0.1f;
	float shootTimer = 0.f;
	int maxHp = 28;
	int hp = 0;

	bool isDamage = true;
	
	float damageTimer = 0;


	float idleShootTimer = 0;

	int life = 3;


	bool isDead = false;
	float deadTimer = 0.f;
	float ladderTimer = 0.f;


public:
	AniPlayer(const std::string& name = "");
	~AniPlayer() = default;

	void SetIsGround(bool ground) { isGround = ground; }
	void SetIsGrounded() { isGrounded = true; }
	void SetIsLadder(bool ladder) { isLadder = ladder; }
	
	void IsDamage() { isDamage = !isDamage; }
	void SetIsCeiling() {
		velocity.y = 0.f;
		position.y += 1.f; 
	}
	void SetIsWallLeft() {
		velocity.x = 0.f;
		position.x += 0.1f; 
		
	}
	void SetIsWallRight() {
		velocity.x = 0.f;
		position.x -= 0.1f; 
		
	}

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	sf::FloatRect GetLocalBounds() const override
	{
		return body.getLocalBounds();
	}

	sf::FloatRect GetGlobalBounds() const override
	{
		return body.getGlobalBounds();
	}



	void Shoot();
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void OnDamage(int damage);
};
