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
	texIds.push_back("graphics/monster.png");

	std::vector<std::string> texList = {
		"map/gameui.png",
		"map/gameround1.png",
	};
	TEXTURE_MGR.Load(texList);
	TEXTURE_MGR.Load("graphics/monster.png");
	ANI_CLIP_MGR.Load("animations/monsterCol1.csv");

	AddGameObject(new Monster());
	Scene::Init();

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
	monsterTimer += dt;
	if (monsterTimer > 1.0f)
	{
		std::cout << "Monster Spawn" << std::endl;
		MonsterSpawn(1);
		monsterTimer = 0.0f;
	}

	//if (tileMap)
	//	tileMap->Update(dt);


}

void SceneRound1::Draw(sf::RenderWindow& window)
{
	//sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	//sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
	//std::cout << "Mouse Pixel: ("
	//	<< pixelPos.x << ", " << pixelPos.y << ")  "
	//	<< "World Pos: ("
	//	<< worldPos.x << ", " << worldPos.y << ")"
	//	<< std::endl;

	window.draw(BackgroundSprite);
	Scene::Draw(window);
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
			monster->Init();
		}
		sf::Vector2f spawnPos;
		spawnPos.x = Utils::RandomRange(-20, -10);
		spawnPos.y = Utils::RandomRange(400, 630);
		monster->SetPosition(spawnPos);
		monster->Reset();	
		
		float xx = 710.f;
		float yy = Utils::RandomRange(400, 630);
		monster->SetArrivePos({ xx,yy });
		monster->Reset();
		monsterList.push_back(monster);
	}
	
}
