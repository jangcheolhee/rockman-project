#include "stdafx.h"
#include "SceneStageChosen.h"
#include "SpriteGo.h"
#include "BasicPlayer.h"

SceneStageChosen::SceneStageChosen()
	:Scene(SceneIds::Chosen)
{
}

void SceneStageChosen::Init()
{
	texIds.push_back("graphics/stageSprite.png");
	texIds.push_back("graphics/woodMan.png");
	


	ANI_CLIP_MGR.Load("animations/woodMan1.csv");

	SpriteGo* background = new SpriteGo("graphics/stageSprite.png");
	background->GetSprite().setTextureRect({776,21,256,256});
	background->sortingLayer = SortingLayers::Background;
	background->sortingOrder = 0;
	AddGameObject(background);

	boss = new BasicPlayer("Boss");
	boss->sortingLayer = SortingLayers::Foreground;
	boss->sortingOrder = 0;
	boss->SetPosition({ 110,98 });
	boss->SetOrigin(Origins::BC);
	
	AddGameObject(boss);


	Scene::Init();

}

void SceneStageChosen::Enter()
{
	worldView.setSize({ 256,256 });
	worldView.setCenter({ 128,128 });
	Scene::Enter();
	
	music.openFromFile("sounds/Stage Chosen.flac");
	music.play();
	timer = 0;

}

void SceneStageChosen::Exit()
{
	music.stop();
	Scene::Exit();
}

void SceneStageChosen::Update(float dt)
{
	timer += dt;
	if (timer > 6) {
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}
	Scene::Update(dt);
}
void SceneStageChosen::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
