#include "stdafx.h"
#include "SceneGame.h"
#include "TextGo.h"
#include "AniPlayer.h"
#include "SpriteGo.h"
#include "TileCollision.h"
#include "Enemy.h"

SceneGame::SceneGame() : Scene(SceneIds::Game)
{
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
	playerInitPos = { 300,182 };

	

	for (int i = 0; i < 100; i++)
	{
		Enemy* bat = (Enemy*)AddGameObject(new Enemy());
		bat->SetActive(false);
		enemyPool.push_back(bat);
	}
	Scene::Init();
}

void SceneGame::Enter()
{
	music.openFromFile("sounds/WoodMan.flac");
	music.play();
	auto size = FRAMEWORK.GetWindowSizeF();
	center ={ size.x * 0.5f, size.y * 0.5f };
	uiView.setSize(size);
	uiView.setCenter(center);
	
	player->SetPosition(playerInitPos);
	
	
	worldView.setSize({512,160});
	worldView.setCenter(player->GetPosition());
	
	SpriteGo* background = new SpriteGo("graphics/map.png");
	background->sortingLayer = SortingLayers::Background;
	background->sortingOrder = 0;
	tileCollision = new TileCollision();
	tileCollision->loadFromFile("graphics/WoodManStage.png");
	
	
	AddGameObject(background);

	for (int i = 0; i < 10; i++)
	{
		enemyPos.push_back({ 347.f + 100 * i, (float)Utils::RandomRange(90, 120)});
	}
	SpawnBats(10);
	Scene::Enter();
}

void SceneGame::Update(float dt)
{

	Scene::Update(dt);
	float x = Utils::Clamp(player->GetPosition().x, center.x, 4000);
	float y = Utils::Clamp(player->GetPosition().y, 0, 800);
	worldView.setCenter({x, y});
	sf::Vector2f pos = player->GetPosition();
	
	if (tileCollision->getTileType(pos.x , pos.y) == TileType::BLOCK)
	{
		player->SetIsGround();
		player->SetIsLadder();
	}

	else if (tileCollision->getTileType(pos.x, pos.y) == TileType::LADDER)
	{
		player->SetIsLadder();
	}
	
	
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);


}

void SceneGame::SpawnBats(int count)
{
	for (int i = 0; i < count  - 5; i++)
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
		enemy->SetType(Enemy::Types::Bat);
		enemy->Reset();
		enemy->SetPosition(enemyPos[i]);


		enemyList.push_back(enemy);
	}

	for (int i = 5; i < count; i++)
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
		enemy->SetType(Enemy::Types::Rabbit);
		enemy->Reset();
		enemy->SetPosition(enemyPos[i]);


		enemyList.push_back(enemy);
	}
}

bool SceneGame::FloorCheck(float x, float y)
{
	return tileCollision->getTileType(x, y) == TileType::BLOCK;
}

