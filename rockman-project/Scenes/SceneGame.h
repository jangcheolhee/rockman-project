#pragma once
#include "Scene.h"
class AniPlayer;
class TileCollision;
class Enemy;
class SceneGame : public Scene
{
protected:
	AniPlayer* player;

	sf::Vector2f center;
	
	sf::Vector2f playerInitPos;
	TileCollision* tileCollision;
	std::list<Enemy*> enemyList;
	std::list<Enemy*>enemyPool;
	std::vector<sf::Vector2f> enemyPos;
	sf::Music music;
	
public:
	SceneGame();
	TileCollision& getTileCollision() { return *tileCollision; }

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window);
	void SpawnBats(int count);
	const std::list<Enemy*>& GetEnemies() const { return enemyList; }
	bool FloorCheck(float x, float y);

};

