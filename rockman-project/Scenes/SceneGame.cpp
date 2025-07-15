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
	TextGo* go = new TextGo("fonts/DS-DIGIT.ttf");
	go->SetString("Game");
	go->SetCharacterSize(30);
	go->SetFillColor(sf::Color::White);
	go->sortingLayer = SortingLayers::UI;
	go->sortingOrder = 0;

	AddGameObject(go);
	
	player = (AniPlayer*)AddGameObject(new AniPlayer("AniPlayer"));
	playerInitPos = { 300,182 };

	bat = (Enemy*)AddGameObject(new Enemy());

	for (int i = 0; i < 100; i++)
	{
		Enemy* bat = (Enemy*)AddGameObject(new Enemy());
		bat->SetActive(false);
		batPool.push_back(bat);
	}
	Scene::Init();
}

void SceneGame::Enter()
{
	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center { size.x * 0.5f, size.y * 0.5f };
	uiView.setSize(size);
	uiView.setCenter(center);
	
	player->SetPosition(playerInitPos);
	bat->SetPosition({ 300.f,200.f });
	
	worldView.setSize({512,160});
	worldView.setCenter(player->GetPosition());
	
	SpriteGo* background = new SpriteGo("graphics/map.png");
	background->sortingLayer = SortingLayers::Background;
	background->sortingOrder = 0;
	tileCollision = new TileCollision();
	tileCollision->loadFromFile("graphics/WoodManStage.png");
	
	
	AddGameObject(background);
	
	enemyPos.push_back({ 347.f,200.f });
	enemyPos.push_back({ 419.f,180.f });
	enemyPos.push_back({ 500.f,200.f });
	SpawnBats(3);
	Scene::Enter();
}

void SceneGame::Update(float dt)
{

	Scene::Update(dt);
	worldView.setCenter(player->GetPosition());
	sf::Vector2f pos = player->GetPosition();
	
	if (tileCollision->getTileType(pos.x, pos.y) == TileType::BLOCK)
	{
		player->SetIsGround();
	}
	else if (tileCollision->getTileType(pos.x, pos.y) == TileType::LADDER)
	{
		//player->SetIsLadder();
	}
	
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);


}

void SceneGame::SpawnBats(int count)
{
	for (int i = 0; i < count; i++)
	{
		Enemy* enemy = nullptr;
		if (batPool.empty())
		{
			enemy = (Enemy*)AddGameObject(new Enemy());
			enemy->Init();

		}
		else
		{
			enemy = batPool.front();
			batPool.pop_front();
			enemy->SetActive(true);
		}
		enemy->SetType(Enemy::Types::Bat);
		enemy->Reset();
		enemy->SetPosition(enemyPos[i]);


		batList.push_back(enemy);
	}
}
