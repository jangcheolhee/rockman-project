#pragma once
#include "Scene.h"
class BasicPlayer;

class SceneTitle : public Scene
{
protected:
	BasicPlayer* player;
public:
	SceneTitle();

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window);
};

