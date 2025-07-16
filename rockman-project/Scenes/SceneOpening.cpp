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
	worldView.setSize({ 256, 256 });
	worldView.setCenter({ 123.f, 123.f });
	
	Scene::Enter();
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

