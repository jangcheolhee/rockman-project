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
	background->SetScale({ 4.f,4.f });
	AddGameObject(background);
	player = (BasicPlayer*)AddGameObject(new BasicPlayer("Player"));
	player->SetOrigin(Origins::BC);
	player->SetScale({ 4.f,4.f });
	AddGameObject(player);
	Scene::Init();
}

void SceneTitle::Enter()
{
	Scene::Enter();
	
	
	player->SetPosition({ 760,410 });
	openTime = 0; 

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
	if (openTime > 5)
	{
		SCENE_MGR.ChangeScene(SceneIds::Opening);
	}
	Scene::Update(dt);
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
