#include "stdafx.h"
#include "SceneOpening.h"
#include "TextGo.h"
#include "BasicPlayer.h"
SceneOpening::SceneOpening()
	:Scene(SceneIds::Opening)
{
}

void SceneOpening::Init()
{

	texIds.push_back("graphics/TitleScreen.png");

	ANI_CLIP_MGR.Load("animations/opening.csv");

	AddGameObject(new BasicPlayer("Opening"));
	Scene::Init();
}

void SceneOpening::Enter()
{
	
	music.openFromFile("sounds/Opening.flac");
	music.play();
	Scene::Enter();
	worldView.setSize({ 256, 256 });
	worldView.setCenter({ 128.f, 128.f });
}

void SceneOpening::Exit()
{
	music.stop();
	Scene::Exit();
}

void SceneOpening::Update(float dt)
{
	Scene::Update(dt);
	if (InputMgr::GetKeyDown(sf::Keyboard::Return) || InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		SCENE_MGR.ChangeScene(SceneIds::Title);
	}
}
void SceneOpening::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

