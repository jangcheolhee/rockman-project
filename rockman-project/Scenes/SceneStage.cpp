#include "stdafx.h"
#include "SceneStage.h"
#include "SpriteGo.h";

SceneStage::SceneStage()
	:Scene(SceneIds::Stage)
{
}

void SceneStage::Init()
{	
	texIds.push_back("graphics/stageSprite.png");
	SpriteGo* backGround = new SpriteGo("graphics/stageSprite.png");
	backGround->sortingLayer = SortingLayers::Background;
	backGround->sortingOrder = 0;
	backGround->GetSprite().setTextureRect({1,21,256,256});
	
	AddGameObject(backGround);

	selectBox = new SpriteGo("graphics/stageSprite.png");
	selectBox->sortingLayer = SortingLayers::Foreground;
	selectBox->sortingOrder = 0;
	selectBox->GetSprite().setTextureRect({ 201,284,48,48 });
	
	selectBox->SetOrigin(Origins::MC);
	AddGameObject(selectBox);
	Scene::Init();
	
}

void SceneStage::Enter()
{
	
	worldView.setSize({ 256,256 });
	worldView.setCenter({ 128.f, 128.f });
	selectBox->SetPosition({ 128, 112 });
	isFlash = true;
	flashTime = 0;
	stage = 4;
	music.openFromFile("sounds/Stage Select.flac");
	music.play();
	Scene::Enter();
	
}

void SceneStage::Exit()
{
	music.stop();
	Scene::Exit();
}

void SceneStage::Update(float dt)
{
	flashTime += dt;
	if (flashTime > 0.2)
	{
		flashTime = 0;
		isFlash = !isFlash;
	}
	sf::Color color = selectBox->GetSprite().getColor();
	if (isFlash)
	{
		color.a = 0;
	}
	else
	{
		color.a = 255;
	}
	selectBox->GetSprite().setColor(color);

	sf::Vector2f pos = selectBox->GetPosition();
	if (InputMgr::GetKeyDown(sf::Keyboard::Right))
	{
		if (stage % 3 <2)
		{
			stage++;
			pos.x += 64;
		}

	}
	
	if (InputMgr::GetKeyDown(sf::Keyboard::Left))
	{
		if (stage % 3 > 0)
		{
			stage --;
			pos.x -= 64;
		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Up))
	{
		if (stage / 3 > 0)
		{
			stage -= 3;
			pos.y -= 64;
		}
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Down))
	{
		if (stage / 3 < 2)
		{
			stage += 3;
			pos.y += 64;
		}

	}
	selectBox->SetPosition(pos);

	if (InputMgr::GetKeyDown(sf::Keyboard::Return))
	{
		stage = 5;
		switch (stage) 
		{
		case 5:
			SCENE_MGR.ChangeScene(SceneIds::Game);
			break;
		}

	}

	Scene::Update(dt);
}
void SceneStage::Draw(sf::RenderWindow& window)
{
	
	Scene::Draw(window);
}
