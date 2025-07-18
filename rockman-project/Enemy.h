#pragma once
#include "GameObject.h"
#include "Animator.h"
#include "HitBox.h"

class SceneGame;
class AniPlayer;
class Enemy : public GameObject
{

public:
	enum class Types
	{
		Bat,
		Rabbit,
		Count,
	};
protected:
	sf::Sprite body;
	Animator animator;
	SceneGame* sceneGame = nullptr;
	AniPlayer* player;

	sf::Vector2f gravity = { 0.f, 500.f };
	sf::Vector2f velocity = { 0.f, 0.f };
	sf::Vector2f initPosition;
	HitBox hitBox;

	int hp = 0;
	float speed = 0.f;
	
	Types type = Types::Bat;
	sf::Vector2f direction;
	float moveInetrval = 0.f;
	float moveTimer = 0.f;
	int damage = 0;
	int attackInterval = 0.f;

	bool isAlive = true;

public:
	Enemy(const std::string& name = "");
	~Enemy() = default;


	void SetInitPosition(sf::Vector2f pos) { initPosition = pos; }
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
	
	void SetAlive(bool b) { isAlive = b; }
	bool IsAlive() { return isAlive; }

	const HitBox& GetHitBox() const { return hitBox; }
	void OnDamage(int damage);
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	
	virtual void UpdateBehavior(float dt) = 0; // 각 적 클래스가 구현
	
	void SetType(Types type);


};

