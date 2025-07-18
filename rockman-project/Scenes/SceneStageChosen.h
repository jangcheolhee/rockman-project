#pragma once
#include "Scene.h"

class BasicPlayer;
class SceneStageChosen :  public Scene
{
protected:
	
	BasicPlayer* boss;
	sf::Music music;
	float timer;
public:

	SceneStageChosen();


	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window);
};

