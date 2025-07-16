#pragma once
#include "Scene.h"
#include "Enemy.h"
class AniPlayer;
class TileCollision;

struct MapZone
{
	sf::FloatRect bounds; // 구간 영역 (x, y, width, height)
	int zoneId;           // 구역 id
	// 추가 정보
	std::function<void()> onEnter; // 진입 시 이벤트
	std::function<void()> onExit;  // 이탈 시 이벤트
	bool entered = false; // 현재 들어와 있는지 여부
};
class SceneGame : public Scene
{
protected:

	std::vector<MapZone> mapZones;
	AniPlayer* player;

	int zoneID= -1;
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
	
	void InitZones();
	void UpdateZones();
	void ClearEnemy();


	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window);




	void SpawnEnemy(sf::Vector2f pos, Enemy::Types type);
	const std::list<Enemy*>& GetEnemies() const { return enemyList; }


	void CheckCollisions();
	bool FloorCheck(float x, float y);

};

