#pragma once
#include "Scene.h"
class AniPlayer;
class TileCollision;
class Enemy;
class SceneGame : public Scene
{
protected:
	AniPlayer* player;
	Enemy* bat;
	sf::Vector2f playerInitPos;
	TileCollision* tileCollision;
	std::list<Enemy*> batList;
	std::list<Enemy*>batPool;
	std::vector<sf::Vector2f> enemyPos;
	
public:
	SceneGame();
	TileCollision& getTileCollision() { return *tileCollision; }

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window);
	void SpawnBats(int count);
	const std::list<Enemy*>& GetEnemies() const { return batList; }
};

