#pragma once
#include "Scene.h"
class BasicPlayer;
class SpriteGo;

class SceneTitle : public Scene
{
protected:
	BasicPlayer* player;
	SpriteGo* background;
	float openTime = 0;

public:
	SceneTitle();

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window);
};

