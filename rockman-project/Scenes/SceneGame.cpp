#include "stdafx.h"
#include "SceneGame.h"

#include "TextGo.h"
#include "AniPlayer.h"
#include "SpriteGo.h"
#include "TileCollision.h"


SceneGame::SceneGame() : Scene(SceneIds::Game)
{
}

void SceneGame::InitZones()
{
	mapZones.clear();

	mapZones.push_back({
	  sf::FloatRect(0, 0, 1273, 248),
	  1,
	  [this]()
		{
			std::cout << "Zone 1 Enter" << std::endl;
			SpawnEnemy({ 200.f,100.f }, Enemy::Types::Bat);
			SpawnEnemy({ 300.f,100.f }, Enemy::Types::Bat);
			SpawnEnemy({ 400.f,100.f }, Enemy::Types::Bat);
			SpawnEnemy({ 500.f,100.f }, Enemy::Types::Bat);
			SpawnEnemy({ 600.f,100.f }, Enemy::Types::Bat);
			SpawnEnemy({ 700.f,100.f }, Enemy::Types::Bat);
			SpawnEnemy({ 800.f,100.f }, Enemy::Types::Bat);
			SpawnEnemy({ 1000.f,100.f }, Enemy::Types::Rabbit);
			SpawnEnemy({ 800.f,100.f }, Enemy::Types::Rabbit);
		},
	  [this]()
		{
			std::cout << "Zone 1 Exit" << std::endl;
			ClearEnemy();
		},
	  false
		});

	// Zone 2
	mapZones.push_back({
		sf::FloatRect(1026, 250, 249, 267),
		2,
		[this]()
		{ 
			std::cout << "Zone 2 Enter" << std::endl;
			SpawnEnemy({ 1070.f, 320.f }, Enemy::Types::Bat);
			SpawnEnemy({ 1370.f, 320.f }, Enemy::Types::Bat);
			SpawnEnemy({ 1270.f, 300.f }, Enemy::Types::Bat);
		},
		[this]()
		{ 
			std::cout << "Zone 2 Exit" << std::endl;
			ClearEnemy();
		},
		false
		});
}

void SceneGame::UpdateZones()
{
	sf::Vector2f playerPos = player->GetPosition();

	for (auto& zone : mapZones)
	{
		bool nowInZone = zone.bounds.contains(playerPos);

		if (nowInZone && !zone.entered)
		{
			zone.entered = true;
			zoneID = zone.zoneId;
			if (zone.onEnter) zone.onEnter();
		}
		else if (!nowInZone && zone.entered)
		{
			zone.entered = false;
			if (zone.onExit) zone.onExit();
		}
	}
}

void SceneGame::ClearEnemy()
{
	for (Enemy* enemy : enemyList)
	{
		enemy->SetActive(false);
		enemyPool.push_back(enemy);
	}
	enemyList.clear();
}

void SceneGame::Init()
{

	texIds.push_back("graphics/megaman_sprite.png");
	texIds.push_back("graphics/map.png");
	texIds.push_back("graphics/WoodManStage.png");
	texIds.push_back("graphics/bullet.png");
	texIds.push_back("graphics/enemy.png");
	fontIds.push_back("fonts/DS-DIGIT.ttf");

	ANI_CLIP_MGR.Load("animations/idle.csv");
	ANI_CLIP_MGR.Load("animations/run.csv");
	ANI_CLIP_MGR.Load("animations/jump.csv");
	ANI_CLIP_MGR.Load("animations/shoot1.csv");
	ANI_CLIP_MGR.Load("animations/shoot.csv");
	ANI_CLIP_MGR.Load("animations/bat.csv");
	ANI_CLIP_MGR.Load("animations/bat2.csv");
	ANI_CLIP_MGR.Load("animations/rabbit.csv");

	TextGo* go = new TextGo("fonts/DS-DIGIT.ttf");
	go->SetString("Game");
	go->SetCharacterSize(30);
	go->SetFillColor(sf::Color::White);
	go->sortingLayer = SortingLayers::UI;
	go->sortingOrder = 0;

	AddGameObject(go);

	player = (AniPlayer*)AddGameObject(new AniPlayer("AniPlayer"));
	playerInitPos = { 140,0 };

	InitZones();
	Scene::Init();
}

void SceneGame::Enter()
{
	music.openFromFile("sounds/WoodMan.flac");
	music.play();

	//UI VIEW
	auto size = FRAMEWORK.GetWindowSizeF();
	center = { size.x * 0.5f, size.y * 0.5f };
	uiView.setSize(size);
	uiView.setCenter(center);
	//World View
	worldView.setSize({ 256,256 });
	worldView.setCenter({ 123.f, 123.f });

	SpriteGo* background = new SpriteGo("graphics/map.png");
	background->sortingLayer = SortingLayers::Background;
	background->sortingOrder = 0;
	tileCollision = new TileCollision();
	tileCollision->loadFromFile("graphics/WoodManStage.png");
	player->SetPosition(playerInitPos);

	AddGameObject(background);


	Scene::Enter();
}

void SceneGame::Update(float dt)
{

	Scene::Update(dt);
	float x = Utils::Clamp(player->GetPosition().x, center.x, 4000);
	float y = Utils::Clamp(player->GetPosition().y, 0, 800);
	switch (zoneID)
	{
	case 1:

		worldView.setCenter({ x, y });
		break;

	case 2:
		worldView.setCenter({ 1156,388 });
		break;

	}

	CheckCollisions();
	UpdateZones();

}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);


}

void SceneGame::SpawnEnemy(sf::Vector2f pos, Enemy::Types type)
{

	Enemy* enemy = nullptr;
	if (enemyPool.empty())
	{
		enemy = (Enemy*)AddGameObject(new Enemy());
		enemy->Init();

	}
	else
	{
		enemy = enemyPool.front();
		enemyPool.pop_front();
		enemy->SetActive(true);
	}
	enemy->SetType(type);
	enemy->Reset();
	enemy->SetPosition(pos);


	enemyList.push_back(enemy);



}

void SceneGame::CheckCollisions()
{
	sf::Vector2f pos = player->GetPosition();

	if (tileCollision->getTileType(pos.x, pos.y) == TileType::BLOCK || tileCollision->getTileType(pos.x, pos.y) == TileType::LADDER)
	{
		player->SetIsGround();

	}
	// 위 충돌 검사
	if (tileCollision->getTileType(pos.x, pos.y - player->GetLocalBounds().height - 1) == TileType::BLOCK)
	{
		player->SetIsCeiling();

	}
	// 왼쪽 충돌 검사
	if (tileCollision->getTileType(pos.x - player->GetLocalBounds().width / 2 - 1, pos.y - player->GetLocalBounds().height / 2) == TileType::BLOCK)
	{
		player->SetIsWallLeft();
	}
	// 오른쪽 충돌 검사
	if (tileCollision->getTileType(pos.x + player->GetLocalBounds().width / 2 + 1, pos.y - player->GetLocalBounds().height / 2) == TileType::BLOCK)
	{
		player->SetIsWallRight();
	}

	// 사다리 검사
	if (tileCollision->getTileType(pos.x, pos.y + 1) == TileType::LADDER || tileCollision->getTileType(pos.x, pos.y - player->GetLocalBounds().height - 1) == TileType::LADDER)
	{
		player->SetIsLadder();
	}
	else
	{
		player->SetLadder();
	}
}

bool SceneGame::FloorCheck(float x, float y)
{
	return tileCollision->getTileType(x, y) == TileType::BLOCK || tileCollision->getTileType(x, y) == TileType::LADDER;
}

