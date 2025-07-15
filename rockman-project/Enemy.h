#pragma once
#include "GameObject.h"
#include "Animator.h"
#include "SceneGame.h"
#include "HitBox.h"
class AniPlayer;
class Enemy : public GameObject
{
public:
	enum class Types
	{
		Bat,
		Rabbit,
		Total,
	};
protected:
	sf::Sprite body;
	Animator animator;
	SceneGame* sceneGame = nullptr;
	sf::Vector2f gravity = { 0.f, 500.f };
	sf::Vector2f velocity = { 0.f, 0.f };
	HitBox hitBox;
	int hp;
	Types type = Types::Bat;
	AniPlayer* player;
	float speed = 0.f;

	sf::Vector2f direction;
	bool isMove = false;

public:
	Enemy(const std::string& name = "");
	~Enemy() = default;



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
	
	const HitBox& GetHitBox() const { return hitBox; }
	void OnDamage(int damage);
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetType(Types type);
};

