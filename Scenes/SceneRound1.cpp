#include "stdafx.h"
#include "SceneRound1.h"
#include "TileMap.h"
#include "ResourceMgr.h"
#include <SFML/Graphics.hpp>
#include <algorithm>

SceneRound1::SceneRound1()
	: Scene(SceneIds::Round1)
{
}


void SceneRound1::Init()
{
	
	std::vector<std::string> texList = {
		"map/gameui.png",
		"map/gameround1.png"
	};
	TEXTURE_MGR.Load(texList);

	Scene::Init();

	/*float mapScale = 1.f;
	tileMap = new TileMap("tileMap");
	tileMap->Load("map/untitled.tmx", "map/round1total.png");
	tileMap->Init();
	tileMap->setScale(mapScale, mapScale)*/;	

	sf::Texture& uiTex = TEXTURE_MGR.Get("map/gameui.png");
	uiSprite.setTexture(uiTex);
	uiSprite.setScale(1.5f, 2.f);

	sf::Texture& BackTex = TEXTURE_MGR.Get("map/gameround1.png");
	BackgroundSprite.setTexture(BackTex);
	BackgroundSprite.setScale(1.5f, 2.f);
}

void SceneRound1::Enter()
{
	Scene::Enter();
}


void SceneRound1::Update(float dt)
{
	Scene::Update(dt);

	//if (tileMap)
	//	tileMap->Update(dt);
}

void SceneRound1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	//if (tileMap)
	//	tileMap->Draw(window);
	window.draw(BackgroundSprite);
	window.draw(uiSprite);
}
void SceneRound1::Release()
{

	Scene::Release();
}