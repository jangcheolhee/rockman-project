#pragma once
#include "GameObject.h"
#include "Animator.h"
class BasicPlayer :
    public GameObject
{
protected:
	sf::Sprite body;
	Animator animator;
	float speed = 0.f;

public:
	BasicPlayer(const std::string& name = "");
	virtual ~BasicPlayer() = default;

	void changeAni();
	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

