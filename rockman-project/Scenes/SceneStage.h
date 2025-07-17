#pragma once
#include "Scene.h"
class SpriteGo;

class SceneStage :  public Scene
{
protected:
	SpriteGo* selectBox;
	float flashTime = 0.f;
	bool isFlash = false;
	int stage = -1;
public:

	SceneStage();


	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window);
};

