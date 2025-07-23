#include "stdafx.h"
#include "SceneRound1.h"
#include "TileMap.h"
#include "ResourceMgr.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "Monster.h"

SceneRound1::SceneRound1()
	: Scene(SceneIds::Round1)
{
}


void SceneRound1::Init()
{
	
	std::vector<std::string> texList = {
		"map/gameui.png",
		"map/gameround1.png",
		"graphics/monster.png"
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
	/*sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
	std::cout << "Mouse Pixel: ("
		<< pixelPos.x << ", " << pixelPos.y << ")  "
		<< "World Pos: ("
		<< worldPos.x << ", " << worldPos.y << ")"
		<< std::endl;*/
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

void SceneRound1::MonsterSpawn(int count)
{
	for (int i=0; i<count;++i)
	{
		Monster* monster = nullptr;
		if (monsterPool.empty())
		{
			monster = (Monster*)AddGameObject(new Monster());
			monster->Init();
		}
		else
		{
			monster = monsterPool.front();
			monsterPool.pop_back();
			monster->SetActive(true);
		}

		monster->SetType((Monster::Types)Utils::RandomRange(0, Monster::TotalTypes));
		sf::Vector2f spawnPos;
		spawnPos.x = Utils::RandomRange(-20, -10);
		spawnPos.y = Utils::RandomRange(200, 310);
		monster->SetPosition(spawnPos);
		monster->Reset();	


		monsterList.push_back(monster);
	}
	
}
