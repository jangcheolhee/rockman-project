#pragma once
#include "Scene.h"
class SceneOpening : public Scene
{
protected:
	sf::Music music;;
public:
	SceneOpening();


	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window);
};