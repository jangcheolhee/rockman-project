#include "stdafx.h"
#include "SceneGame.h"
#include "TextGo.h"
#include "AniPlayer.h"
#include "SpriteGo.h"

SceneGame::SceneGame() : Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	texIds.push_back("graphics/megaman_sprite.png");
	texIds.push_back("graphics/map.png");
	fontIds.push_back("fonts/DS-DIGIT.ttf");

	ANI_CLIP_MGR.Load("animations/idle.csv");
	ANI_CLIP_MGR.Load("animations/run.csv");
	ANI_CLIP_MGR.Load("animations/jump.csv");

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
	AddGameObject(background);
	player = (AniPlayer*)AddGameObject(new AniPlayer());

	Scene::Init();
}

void SceneGame::Enter()
{
	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center { size.x * 0.5f, size.y * 0.5f };
	uiView.setSize(size);
	uiView.setCenter(center);
	
	player->SetPosition({ 100,100 });
	
	
	worldView.setSize({size.x / 2, size.y / 2});
	worldView.setCenter(player->GetPosition());

	

	Scene::Enter();
}

void SceneGame::Update(float dt)
{

	Scene::Update(dt);
	worldView.setCenter(player->GetPosition());
	
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);


}
