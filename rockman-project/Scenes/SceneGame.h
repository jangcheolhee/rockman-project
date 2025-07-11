#pragma once
#include "Scene.h"
class AniPlayer;
class SceneGame : public Scene
{
protected:
	AniPlayer* player;
	
public:
	SceneGame();

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window);

};

