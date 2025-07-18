#include "stdafx.h"
#include "Particle.h"

Particle::Particle(const sf::Vector2f& pos, const sf::Vector2f& vel, const std::string& name)
	:GameObject(name)
{
	
	body.setPosition(pos);
	velocity = vel;
}

void Particle::Init()
{
    animator.SetTarget(&body);
    Utils::SetOrigin(body, Origins::MC);
    
}

void Particle::Reset()
{
    
    animator.Play("animations/particle.csv");
    

}

void Particle::Release()
{
}

void Particle::Update(float dt)
{
    animator.Update(dt);
    elapsed += dt;
    if (elapsed >= lifeTime)
    {
        SetActive(false);
        return;
    }

    body.move(velocity * dt);

    // 중력 제거: velocity.y += 300.f * dt; 삭제

    // 점점 사라짐
    sf::Color c = body.getColor();
    c.a = static_cast<sf::Uint8>(255 * (1 - elapsed / lifeTime));
    body.setColor(c);
}

void Particle::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
