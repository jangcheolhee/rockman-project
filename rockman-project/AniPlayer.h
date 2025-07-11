#pragma once
#include "Animator.h"
#include "HitBox.h"


class SceneGame;
class AniPlayer : public GameObject
{
protected:
	sf::Sprite body;
	Animator animator;

	sf::Vector2f gravity = { 0.f, 500.f };
	sf::Vector2f velocity = { 0.f, 0.f };
	bool isGrounded = true;
	bool isGround = false;
	float speed = 100.f;
	HitBox hitbox;
	SceneGame* sceneGame = nullptr;


public:
	AniPlayer(const std::string& name = "");
	~AniPlayer() = default;

	void SetIsGround() { isGround = true; }
	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};
