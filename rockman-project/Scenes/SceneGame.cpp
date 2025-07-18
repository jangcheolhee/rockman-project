#include "stdafx.h"
#include "SceneGame.h"

#include "TextGo.h"
#include "AniPlayer.h"
#include "SpriteGo.h"
#include "TileCollision.h"
#include "HpBar.h"
#include "BatEnemy.h"


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

			SpawnEnemy({ 350.f,100.f }, Enemy::Types::Bat);
			SpawnEnemy({ 300.f,100.f }, Enemy::Types::Bat);
			SpawnEnemy({ 400.f,100.f }, Enemy::Types::Bat);
			SpawnEnemy({ 500.f,100.f }, Enemy::Types::Bat);
			SpawnEnemy({ 600.f,100.f }, Enemy::Types::Bat);
			SpawnEnemy({ 700.f,100.f }, Enemy::Types::Bat);
			SpawnEnemy({ 800.f,100.f }, Enemy::Types::Bat);
		},
	  [this]()
		{
			std::cout << "Zone 1 Exit" << std::endl;

			DeleteEnemy();

		},
	  false
		});

	// Zone 2
	mapZones.push_back({
		sf::FloatRect(1025, 250, 256, 256),
		2,
		[this]()
		{
			std::cout << "Zone 2 Enter" << std::endl;
			worldView.setCenter({ 1153,388 });
			SpawnEnemy({ 1082.f , 368.f + 25 }, Enemy::Types::Bat);
			SpawnEnemy({ 1122, 385.f + 25 }, Enemy::Types::Bat);
			SpawnEnemy({ 1153.f, 353.f + 25 }, Enemy::Types::Bat);
		},
		[this]()
		{
			std::cout << "Zone 2 Exit" << std::endl;
			DeleteEnemy();
		},
		false
		});
	// Zone 3
	mapZones.push_back({
		sf::FloatRect(1025, 515, 256, 256),
		3,
		[this]()
		{
			std::cout << "Zone 3 Enter" << std::endl;
			worldView.setCenter({ 1153,640 });

		},
		[this]()
		{
			std::cout << "Zone 3 Exit" << std::endl;
			DeleteEnemy();
		},
		false
		});
	mapZones.push_back({
		sf::FloatRect(1281, 515, 256, 256),
		4,
		[this]()
		{
			worldView.setCenter({ 1409,640 });
			std::cout << "Zone 4 Enter" << std::endl;

		},
		[this]()
		{
			std::cout << "Zone 4 Exit" << std::endl;
			DeleteEnemy();
		},
		false
		});

	mapZones.push_back({
		sf::FloatRect(1537, 515, 256, 256),
		5,
		[this]()
		{
			worldView.setCenter({ 1665,640 });
			std::cout << "Zone 5 Enter" << std::endl;

		},
		[this]()
		{
			std::cout << "Zone 5 Exit" << std::endl;
			DeleteEnemy();
		},
		false
		});
	mapZones.push_back({
		sf::FloatRect(1793, 515, 256, 256),
		6,
		[this]()
		{
			std::cout << "Zone 6 Enter" << std::endl;
			worldView.setCenter({ 1921,640 });
		},
		[this]()
		{
			std::cout << "Zone 6 Exit" << std::endl;
			DeleteEnemy();
		},
		false
		});
	mapZones.push_back({
		sf::FloatRect(1793, 256, 256, 256),
		7,
		[this]()
		{
			std::cout << "Zone 7 Enter" << std::endl;
			worldView.setCenter({ 1921,384 });
		},
		[this]()
		{
			std::cout << "Zone 7 Exit" << std::endl;
			DeleteEnemy();
		},
		false
		});
	mapZones.push_back({
		sf::FloatRect(1793, 1, 1280, 256),
		8,
		[this]()
		{
			std::cout << "Zone 8 Enter" << std::endl;

		},
		[this]()
		{
			std::cout << "Zone 8 Exit" << std::endl;
			DeleteEnemy();

		},
		false
		});
	mapZones.push_back({
		sf::FloatRect(2817, 257, 256, 256),
		9,
		[this]()
		{
			std::cout << "Zone 9 Enter" << std::endl;
			worldView.setCenter({ 2945,384 });

		},
		[this]()
		{
			std::cout << "Zone 9 Exit" << std::endl;
			DeleteEnemy();

		},
		false
		});
	mapZones.push_back({
		sf::FloatRect(2817, 513, 256, 256),
		10,
		[this]()
		{
			std::cout << "Zone 10 Enter" << std::endl;
			worldView.setCenter({ 2945,640 });
		},
		[this]()
		{
			std::cout << "Zone 10 Exit" << std::endl;
			DeleteEnemy();

		},
		false
		});
	mapZones.push_back({
		sf::FloatRect(2817, 769, 256, 226),
		11,
		[this]()
		{
			std::cout << "Zone 11 Enter" << std::endl;
			worldView.setCenter({ 2945,860 });
		},
		[this]()
		{
			std::cout << "Zone 11 Exit" << std::endl;
			player->SetPosition({ 2857,1038 });
			DeleteEnemy();

		},
		false
		});
	mapZones.push_back({
		sf::FloatRect(2817, 1028, 752, 226),
		12,
		[this]()
		{
			std::cout << "Zone 12 Enter" << std::endl;

		},
		[this]()
		{
			std::cout << "Zone 12 Exit" << std::endl;

			DeleteEnemy();
			SCENE_MGR.ChangeScene(SceneIds::Ending);

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



void SceneGame::Init()
{

	texIds.push_back("graphics/megaman_sprite.png");
	texIds.push_back("graphics/map.png");
	texIds.push_back("graphics/WoodManStage.png");
	texIds.push_back("graphics/bullet.png");
	texIds.push_back("graphics/enemy.png");
	texIds.push_back("graphics/energyBars.png");

	fontIds.push_back("fonts/DS-DIGIT.ttf");

	ANI_CLIP_MGR.Load("animations/idle.csv");
	ANI_CLIP_MGR.Load("animations/run.csv");
	ANI_CLIP_MGR.Load("animations/jump.csv");
	ANI_CLIP_MGR.Load("animations/shoot1.csv");
	ANI_CLIP_MGR.Load("animations/shoot.csv");
	ANI_CLIP_MGR.Load("animations/bat.csv");
	ANI_CLIP_MGR.Load("animations/bat2.csv");
	ANI_CLIP_MGR.Load("animations/rabbit.csv");
	ANI_CLIP_MGR.Load("animations/ladder.csv");

	TextGo* go = new TextGo("fonts/DS-DIGIT.ttf");
	go->SetString("Game");
	go->SetCharacterSize(30);
	go->SetFillColor(sf::Color::White);
	go->sortingLayer = SortingLayers::UI;
	go->sortingOrder = 0;

	AddGameObject(go);



	SpriteGo* background = new SpriteGo("graphics/map.png");
	background->sortingLayer = SortingLayers::Background;
	background->sortingOrder = 0;
	tileCollision = new TileCollision();
	tileCollision->loadFromFile("graphics/WoodManStage.png");
	AddGameObject(background);

	hpBar = new HpBar("HpBar");
	AddGameObject(hpBar);

	InitZones();
	player = (AniPlayer*)AddGameObject(new AniPlayer("AniPlayer"));
	playerInitPos = { 140,0 };
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
	worldView.setCenter({ 128.f, 128.f });






	Scene::Enter();
	player->SetPosition({ 100,50 });

}

void SceneGame::Exit()
{
	mapZones[zoneID - 1].entered = false;
	if (mapZones[zoneID - 1].onExit) mapZones[zoneID - 1].onExit();
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	switch (zoneID) // 맵에 제한 둘때만 사용하자 ex) 카메라 워킹 || 몬스터 잡아야 넘어가기
	{
	case 1:
	{
		float x = Utils::Clamp(player->GetPosition().x, center.x, 1100);
		worldView.setCenter({ x, 128 });
		break;
	}
	case 2:
	{
		bool success = true;
		auto it = enemyList.begin();
		while (it != enemyList.end())
		{
			if (!(*it)->GetActive())
			{

				success = false;
				
			}

			std::cout << (*it)->GetActive();
			it++;
		}
		std::cout << success <<std::endl;
		float minY = 250;
		float maxY = minY + 255.f;

		if (!success)
		{
			float clampedY = Utils::Clamp(player->GetPosition().y, minY, maxY);
			player->SetPosition({ player->GetPosition().x, clampedY });
		}
		break;
	}
	case 8:
	{
		float x = Utils::Clamp(player->GetPosition().x, 1921, 2935);
		worldView.setCenter({ x, 128 });
		if (player->GetPosition().x > 2048 && player->GetPosition().x < 2800 && player->GetPosition().y > 300)
		{
			player->OnDamage(50);
		}
		break;
	}
		

	case 12:
	{
		float x = Utils::Clamp(player->GetPosition().x, 2945, 3697);
		worldView.setCenter({ x, 1153 });
		break;
	}

	}
	CheckEnemy();
	CheckCollisions();
	UpdateZones();

#ifdef DEF_DEV
	if (InputMgr::GetKeyDown(sf::Keyboard::F1))
	{
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::F2))
	{
		SCENE_MGR.ChangeScene(SceneIds::Stage);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::F3))
	{
		SCENE_MGR.ChangeScene(SceneIds::Ending);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Comma))
	{
		player->IsDamage();
	}
#endif
	

}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);


}

void SceneGame::CheckEnemy()
{
	
	sf::FloatRect view(
		worldView.getCenter().x - worldView.getSize().x / 2.f,
		worldView.getCenter().y - worldView.getSize().y / 2.f,
		worldView.getSize().x,
		worldView.getSize().y
	);
	auto it = enemyList.begin();
	while (it != enemyList.end())
	{
		
		if (view.contains((*it)->GetPosition()) )
		{

			if (!(*it)->GetActive() && (*it)->IsAlive())
			{
				(*it)->Reset();
				(*it)->SetActive(true);

			}
		}
		else
		{
			(*it)->SetAlive(true);
			if ((*it)->GetActive())
			{
				(*it)->SetActive(false);
				
			}
		
		}
		it++;
	}
}
void SceneGame::DeleteEnemy()
{
	auto it = enemyList.begin();
	while (it != enemyList.end())
	{
		RemoveGameObject(*it);
		it = enemyList.erase(it);
		
		
	}
	
}

Enemy* SceneGame::CreateEnemy(Enemy::Types type)
{
	Enemy* enemy = nullptr;

	switch (type)
	{
	case Enemy::Types::Bat:
		enemy = new BatEnemy();
		break;

	case Enemy::Types::Rabbit:
	
		break;

	default:
		break;
	}

	enemy->Init();
	return enemy;
}

void SceneGame::SpawnEnemy(sf::Vector2f pos, Enemy::Types type)
{

	Enemy* enemy = CreateEnemy(type);
	enemy->SetInitPosition(pos);
	enemy->SetType(type);
	enemy->Reset();
	enemy->SetActive(false);
	AddGameObject(enemy);
	enemyList.push_back(enemy);
}

void SceneGame::CheckCollisions()
{
	sf::Vector2f pos = player->GetPosition();

	if (tileCollision->getTileType(pos.x, pos.y) == TileType::BLOCK || tileCollision->getTileType(pos.x, pos.y+1) == TileType::LADDER)
	{
		player->SetIsGround(true);

	}
	// 위 충돌 검사
	if (tileCollision->getTileType(pos.x, pos.y - player->GetLocalBounds().height) == TileType::BLOCK)
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
	if (tileCollision->getTileType(pos.x, pos.y + 1) == TileType::LADDER )
	{
		player->SetIsLadder(true);
	}
	else
	{
		player->SetIsLadder(false);
	}
}

bool SceneGame::FloorCheck(float x, float y)
{
	return tileCollision->getTileType(x, y) == TileType::BLOCK || tileCollision->getTileType(x, y) == TileType::LADDER;
}

