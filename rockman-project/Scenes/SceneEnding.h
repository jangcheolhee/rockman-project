#pragma once
#include "Scene.h"
class SpriteGo;
class SceneEnding :  public Scene
{
protected:
	SpriteGo* background;
	SpriteGo* cursor;
	sf::Vector2f pos;
	int select = -1;

	float timer = 0.f;

	float flashTime = 0.f;
	bool isFlash = false;
	sf::Music music;
	bool isNext = false;

public:
	SceneEnding();
	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window);
};

