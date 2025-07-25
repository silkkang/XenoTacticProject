#include "stdafx.h"
#include "SceneRound1.h"
#include "TileMap.h"
#include "ResourceMgr.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "Monster.h"
#include "TowerBase.h"

SceneRound1::SceneRound1(sf::RenderWindow& window)
	: Scene(SceneIds::Round1), m_window(window), mgrid({ 24.f,32.f }, { 30,15 })
{
}


void SceneRound1::Init()
{

	std::vector<std::string> texList = {
		"map/gameui.png",
		"map/gameround1.png",
		"graphics/pickimage.png",
		"graphics/towerbase.png",
		"graphics/pickimagex.png",
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

	sf::Texture& PickImgae = TEXTURE_MGR.Get("graphics/pickimage.png");
	PickImageSprite.setTexture(PickImgae);
	Utils::SetOrigin(PickImageSprite, Origins::MC);
	PickImageSprite.setScale(2.7f, 3.6f);
	PickImageSprite.setColor(sf::Color(255, 255, 255, 128));

	sf::Texture& PickImgaex = TEXTURE_MGR.Get("graphics/pickimagex.png");
	PickImagexSprite.setTexture(PickImgaex);
	Utils::SetOrigin(PickImagexSprite, Origins::MC);
	PickImagexSprite.setScale(2.7f, 3.6f);
	PickImagexSprite.setColor(sf::Color(255, 255, 255, 128));



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
		//std::cout << "Monster Spawn" << std::endl;
		MonsterSpawn(1);
		monsterTimer = 0.0f;
	}


	//if (tileMap)
	//	tileMap->Update(dt);


}

void SceneRound1::Draw(sf::RenderWindow& window)
{



	window.draw(BackgroundSprite);
	float offsetY = 289.f;
	sf::Transform t;
	t.translate(1.f, offsetY);
	mgrid.draw(window, t);;
	Scene::Draw(window);
	window.draw(uiSprite);


	sf::Vector2i mousePx = sf::Mouse::getPosition(window);
	sf::Vector2f world = window.mapPixelToCoords(mousePx);
	//std::cout << "Mouse Pixel: ("
	//	<< mousePx.x << ", " << mousePx.y << ")  "
	//	<< "World Pos: ("
	//	<< worldPos.x << ", " << worldPos.y << ")"
	//	<< std::endl;

	if (isPlacingWall)
	{
		sf::Vector2f snapped = mgrid.snapPosition(world);
		PickImageSprite.setPosition(snapped);
		PickImagexSprite.setPosition(snapped);
		if (isColliding)
		{
			window.draw(PickImagexSprite);
		}
		if (!isColliding)
		{
			window.draw(PickImageSprite);
		}
	}
}
void SceneRound1::Release()
{

	Scene::Release();
}

void SceneRound1::MonsterSpawn(int count)
{
	for (int i = 0; i < count; ++i)
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

void SceneRound1::OnEvent(const sf::Event& ev)
{
	sf::Vector2i pix{ ev.mouseButton.x, ev.mouseButton.y };
	sf::Vector2f world = m_window.mapPixelToCoords(pix);
	sf::Vector2f snapped = mgrid.snapPosition(world);
	PickImageSprite.setPosition(snapped);
	PickImagexSprite.setPosition(snapped);
	sf::FloatRect pickBounds = PickImageSprite.getGlobalBounds();

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		if (world.x > 740.f && world.x < 800.f &&
			world.y > 75.f && world.y < 155.f)
		{
			std::cout << "Click to tower 1" << std::endl;

			isPlacingWall = true;
		}
	}
	for (auto* tower : towerList)
	{

		if (tower->GetGlobalBounds().intersects(pickBounds))
		{
			std::cout << "°ãÄ§" << std::endl;
			towerColliding = true;
			//m_window.draw(PickImagexSprite);
			break;
		}
		else
		{
			std::cout << "¾È°ãÄ§" << std::endl;
			//m_window.draw(PickImageSprite);
			towerColliding = false;
		}
	}
	for (auto* mo : monsterList)
	{
		if (mo->GetGlobalBounds().intersects(pickBounds))
		{
			std::cout << "°ãÄ§" << std::endl;
			monsterColliding = true;
			//m_window.draw(PickImagexSprite);
			break;
		}
		else
		{
			std::cout << "¾È°ãÄ§" << std::endl;
			//m_window.draw(PickImageSprite);
			monsterColliding = false;
		}
	}
	if(towerColliding || monsterColliding)
	{
		isColliding = true;
	}
	if(!towerColliding && !monsterColliding)
	{
		isColliding = false;
	}
	if (isPlacingWall)
	{
		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			if (world.x > 23.f && world.x < 670.f &&
				world.y > 320.f && world.y < 690.f)
			{
				if (!isColliding)
				{
					std::cout << "No Collision" << std::endl;
					auto pos = PickImageSprite.getPosition();
					auto* Tower = new TowerBase("Base");
					Tower->Init();
					Tower->SetPosition(pos);
					Tower->Reset();
					AddGameObject(Tower);
					towerList.push_back(Tower);
					isPlacingWall = false;
				}
			}
		}

	}

}

