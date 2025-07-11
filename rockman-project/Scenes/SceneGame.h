#pragma once
#include "Scene.h"
class AniPlayer;
class TileCollision;
class SceneGame : public Scene
{
protected:
	AniPlayer* player;
	sf::Vector2f playerInitPos;
	TileCollision* tileCollision;
	
public:
	SceneGame();
	TileCollision& getTileCollision() { return *tileCollision; }

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window);

};

