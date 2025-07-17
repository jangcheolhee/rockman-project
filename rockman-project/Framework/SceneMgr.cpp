#include "stdafx.h"
#include "SceneMgr.h"
#include "SceneOpening.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneStage.h"
#include "SceneEnding.h"

void SceneMgr::Init()
{

	scenes.push_back(new SceneOpening());
	scenes.push_back(new SceneTitle());
	scenes.push_back(new SceneStage());
	scenes.push_back(new SceneGame());
	scenes.push_back(new SceneEnding());
	

	for (auto scene : scenes)
	{
		scene->Init();
	}

	currentScene = startScene;
	scenes[(int)currentScene]->Enter();
}

void SceneMgr::Release()
{
	for (auto scene : scenes)
	{
		if (scene->Id == currentScene)
		{
			scene->Exit();
		}
		scene->Release();
		delete scene;
	}
	scenes.clear();
}

void SceneMgr::ChangeScene(SceneIds id)
{
	nextScene = id;
}

void SceneMgr::Update(float dt)
{
	if (nextScene != SceneIds::None)
	{
		scenes[(int)currentScene]->Exit();
		currentScene = nextScene;
		nextScene = SceneIds::None;
		scenes[(int)currentScene]->Enter();
	}

	scenes[(int)currentScene]->Update(dt);
}

void SceneMgr::Draw(sf::RenderWindow& window)
{
	scenes[(int)currentScene]->Draw(window);
}
