#pragma once
#include "Scene.h"
class SceneOpening : public Scene
{

public:
	SceneOpening();


	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window);
};