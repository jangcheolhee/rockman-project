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

	background = new SpriteGo("graphics/TitleScreen1.png");
	background->sortingLayer = SortingLayers::Background;
	background->sortingOrder = 0;
	
	AddGameObject(background);
	//player = (BasicPlayer*)AddGameObject(new BasicPlayer("Player"));
	Scene::Init();
}

void SceneTitle::Enter()
{
	Scene::Enter();
	background->SetScale({ 4.f, 4.f });
	openTime = 0; 

}

void SceneTitle::Update(float dt)
{
	openTime += dt;
	if (InputMgr::GetKeyDown(sf::Keyboard::Return))
	{
		SCENE_MGR.ChangeScene(SceneIds::Stage);
	}
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
