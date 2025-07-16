#pragma once
#include "Scene.h"
class SceneEnding :  public Scene
{
public:
	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window);
};

