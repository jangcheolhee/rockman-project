#include "stdafx.h"
#include "SceneEnding.h"
#include "SpriteGo.h"

SceneEnding::SceneEnding()
	:Scene(SceneIds::Ending)
{
}

void SceneEnding::Init()
{
	texIds.push_back("graphics/menus.png");

	background = new SpriteGo("graphics/menus.png");
	background->sortingLayer = SortingLayers::Background;
	background->sortingOrder = 0;
	background->GetSprite().setTextureRect({ 523,282,256,256 });
	background->SetScale({ 4.f,4.f });
	AddGameObject(background);

	cursor = new SpriteGo("graphics/menus.png");
	cursor->sortingLayer = SortingLayers::Foreground;
	cursor->sortingOrder = 0;
	cursor->GetSprite().setTextureRect({ 1183,563,8,8 });
	cursor->SetScale({ 4.f,4.f });
	AddGameObject(cursor);
	pos = ScreenToWorld({ 148 ,199 });
	Scene::Init();
}

void SceneEnding::Enter()
{
	Scene::Enter();
	timer = 0;
	background->GetSprite().setTextureRect({ 523,282,256,256 });
	select = 0;
	cursor->SetPosition(pos);
	cursor->SetActive(false);
}

void SceneEnding::Exit()
{
	Scene::Exit();
}

void SceneEnding::Update(float dt)
{
	timer += dt;
	if (timer > 3.5 && timer < 4) 
	{
		background->GetSprite().setTextureRect({1044,282,256,256});
		cursor->SetActive(true);
	}

	flashTime += dt;
	if (flashTime > 0.15)
	{
		flashTime = 0;
		isFlash = !isFlash;
	}
	sf::Color color = cursor->GetSprite().getColor();
	if (isFlash)
	{
		color.a = 0;
	}
	else
	{
		color.a = 255;
	}
	cursor->GetSprite().setColor(color);


	if (InputMgr::GetKeyDown(sf::Keyboard::Up))
	{
		select = (select - 1) % 3;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Down))
	{
		select = (select + 1) % 3;
	}
	switch (select)
	{
	case 0:
		cursor->SetPosition({pos.x, pos. y});
		break;
	case 1:
		cursor->SetPosition({pos.x, pos.y + 64});
		break;
	case 2:
		cursor->SetPosition({ pos.x, pos.y + 128 });
		break;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Return))
	{
		switch (select)
		{
		case 0:
			SCENE_MGR.ChangeScene(SceneIds::Game);
			break;
		case 1:
			SCENE_MGR.ChangeScene(SceneIds::Stage);
			break;
		case 2:
			
			break;
		}
	}
	Scene::Update(dt);
}

void SceneEnding::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
