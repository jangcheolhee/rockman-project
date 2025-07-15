#pragma once
#include "Scene.h"
class AniPlayer;
class TileCollision;
class Bat;
class SceneGame : public Scene
{
protected:
	AniPlayer* player;
	Bat* bat;
	sf::Vector2f playerInitPos;
	TileCollision* tileCollision;
	std::list<Bat*> batList;
	std::list<Bat*>batPool;
	std::vector<sf::Vector2f> enemyPos;
	
public:
	SceneGame();
	TileCollision& getTileCollision() { return *tileCollision; }

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window);
	void SpawnBats(int count);
	const std::list<Bat*>& GetBats() const { return batList; }
};

