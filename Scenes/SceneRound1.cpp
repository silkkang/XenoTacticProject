#include "stdafx.h"
#include "SceneRound1.h"
#include "TileMap.h"


SceneRound1::SceneRound1()
	: Scene(SceneIds::Round1)
{
}


void SceneRound1::Init()
{
	tileMap = new TileMap("tileMap");
	tileMap->Load("map/untitled.tmx", "map/gameround1.png");
	tileMap->Init();

	Scene::Init();
}

void SceneRound1::Enter()
{
	Scene::Enter();
}


void SceneRound1::Update(float dt)
{
	Scene::Update(dt);

	if (tileMap)
		tileMap->Update(dt);
}

void SceneRound1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	if (tileMap)
		tileMap->Draw(window);
}
void SceneRound1::Release()
{

	Scene::Release();
}