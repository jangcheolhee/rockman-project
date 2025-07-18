#include "stdafx.h"
#include "SceneTitle.h"
#include "BasicPlayer.h"
#include <SpriteGo.h>

SceneTitle::SceneTitle()
	:Scene(SceneIds::Title)
{
}

void SceneTitle::Init()
{
	texIds.push_back("graphics/TitleScreen1.png");
	texIds.push_back("graphics/megaman2.png");









	ANI_CLIP_MGR.Load("animations/titleIdle.csv");
	ANI_CLIP_MGR.Load("animations/equip.csv");
	background = new SpriteGo("graphics/TitleScreen1.png");
	background->sortingLayer = SortingLayers::Background;
	background->sortingOrder = 0;
	
	AddGameObject(background);
	player = (BasicPlayer*)AddGameObject(new BasicPlayer("Player"));
	background->sortingLayer = SortingLayers::Foreground;
	background->sortingOrder = 1;
	player->SetOrigin(Origins::BC);
	
	AddGameObject(player);
	Scene::Init();
}

void SceneTitle::Enter()
{
	worldView.setSize({ 256,256 });
	worldView.setCenter({ 128.f, 128.f });
	Scene::Enter();
	music.openFromFile("sounds/Title Screen.flac");
	music.play();
	
	player->SetPosition({ 190,103 });
	openTime = 0; 
	
}

void SceneTitle::Exit()
{
	music.stop();
	Scene::Exit();
}

void SceneTitle::Update(float dt)
{
	
	if (InputMgr::GetKeyDown(sf::Keyboard::Return))
	{
		openTime = 0;
		player->changeAni();
		//SCENE_MGR.ChangeScene(SceneIds::Stage);
	}
	openTime += dt;
	if (openTime > 42)
	{
		SCENE_MGR.ChangeScene(SceneIds::Opening);
	}
	Scene::Update(dt);
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
