#include "stdafx.h"
#include "SceneTitle.h"
#include "BasicPlayer.h"

SceneTitle::SceneTitle()
	:Scene(SceneIds::Title)
{
}

void SceneTitle::Init()
{

	player = (BasicPlayer*)AddGameObject(new BasicPlayer("Player"));
	Scene::Init();
}

void SceneTitle::Enter()
{

	Scene::Enter();
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
