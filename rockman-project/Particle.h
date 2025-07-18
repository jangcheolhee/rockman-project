#pragma once
#include "GameObject.h"
#include "Animator.h"
class Particle : public GameObject
{
protected:
    Animator animator;
    sf::Sprite body;
    sf::Vector2f velocity;
    float lifeTime = 2.f; // 1초간 유지
    float elapsed = 0.f;
public:
    Particle( const sf::Vector2f& pos, const sf::Vector2f& vel, const std::string& name = "");

    void Init() override;
    void Reset() override;
    void Release() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;
};

