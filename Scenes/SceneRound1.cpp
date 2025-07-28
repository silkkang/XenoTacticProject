#include "stdafx.h"
#include "SceneRound1.h"
#include "TileMap.h"
#include "ResourceMgr.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "Monster.h"
#include "TowerBase.h"
#include "Tower1.h"
#include "Tower2.h"
#include "TowerWall.h"
#include "Grid.h"
#include <array>
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
		"tower1/1.png",
		"tower2/1.png",
		"wall/1.png"

	};
	TEXTURE_MGR.Load(texList);
	TEXTURE_MGR.Load("graphics/monster.png");
	ANI_CLIP_MGR.Load("animations/monsterCol1.csv");

	
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
	/*std::cout << "Mouse Pixel: ("
		<< mousePx.x << ", " << mousePx.y << ")  "
		<< "World Pos: ("
		<< world.x << ", " << world.y << ")"
		<< std::endl;*/


	if (isPlacingWall1 || isPlacingWall2|| isPlacingWall3)
	{
		sf::Vector2f snapped = mgrid.snapPosition(world);
		PickImageSprite.setPosition(snapped);
		PickImagexSprite.setPosition(snapped);
		if (world.x > 23.f && world.x < 670.f &&
			world.y > 320.f && world.y < 690.f)
		{
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
			
		}
	
		monster->SetGrid(&mgrid);
		monster->SetTowers(towerList);
		sf::Vector2f spawnPos;

		spawnPos.x = Utils::RandomRange(-20, -10);
		spawnPos.y = Utils::RandomRange(400, 630);
		monster->SetPosition(spawnPos);


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
			std::cout << "Click to wall" << std::endl;

			isPlacingWall1 = true;
		}

		if (world.x > 826.f && world.x < 885.f &&
			world.y > 75.f && world.y < 155.f)
		{
			std::cout << "Click to tower 1" << std::endl;

			isPlacingWall2 = true;
		}

		if (world.x > 903.f && world.x < 967.f &&
			world.y > 75.f && world.y < 155.f)
		{
			std::cout << "Click to tower 1" << std::endl;

			isPlacingWall3 = true;
		}
	}
	for (auto* tower : towerList)
	{

		if (tower->GetGlobalBounds().intersects(pickBounds))
		{
			//std::cout << "°ãÄ§" << std::endl;
			towerColliding = true;
			break;
		}
		else
		{
			//std::cout << "¾È°ãÄ§" << std::endl;
			towerColliding = false;
		}
	}
	for (auto* mo : monsterList)
	{
		if (mo->GetGlobalBounds().intersects(pickBounds))
		{
			//std::cout << "°ãÄ§" << std::endl;
			monsterColliding = true;
			break;
		}
		else
		{
			//std::cout << "¾È°ãÄ§" << std::endl;
			monsterColliding = false;
		}
	}
	if (towerColliding || monsterColliding)
	{
		isColliding = true;
	}
	if (!towerColliding && !monsterColliding)
	{
		isColliding = false;
	}
	if (!isColliding)
	{
		if (isPlacingWall1)
		{
			if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
			{
				if (world.x > 23.f && world.x < 670.f &&
					world.y > 320.f && world.y < 690.f)
				{

					float cw = mgrid.getCellSize().x;
					float ch = mgrid.getCellSize().y;
					int ix = int(std::round(world.x / cw));
					int iy = int(std::round(world.y / ch));


					std::array<sf::Vector2i, 4> quads = { {
						{ix - 1, iy - 1},
						{ ix , iy - 1},
						{ix - 1,  iy },
						{ ix ,  iy }
					} };

					std::vector<sf::Vector2i> occupied;
					for (auto cell : quads)
					{
						int cx = cell.x, cy = cell.y;
						if (!mgrid.isInBounds(cx, cy)) continue;
						mgrid.setBlocked(ix, iy, true);
						occupied.push_back(cell);
					}
					auto* Tower = new TowerBase("Base");
					Tower->Init();
					Tower->SetOccupiedCells(occupied);
					Tower->SetPosition(snapped);
					Tower->Reset();
					AddGameObject(Tower);
					towerList.push_back(Tower);



					auto* wall = new TowerWall("Base1");
					wall->Init();
					wall->SetPosition(snapped);
					wall->Reset();
					AddGameObject(wall);
					isPlacingWall1 = false;
				}
			}
		}
		if (isPlacingWall2)
		{
			if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
			{
				if (world.x > 23.f && world.x < 670.f &&
					world.y > 320.f && world.y < 690.f)
				{

					float cw = mgrid.getCellSize().x;
					float ch = mgrid.getCellSize().y;
					int ix = int(std::round(world.x / cw));
					int iy = int(std::round(world.y / ch));


					std::array<sf::Vector2i, 4> quads = { {
						{ix - 1, iy - 1},
						{ ix , iy - 1},
						{ix - 1,  iy },
						{ ix ,  iy }
					} };

					std::vector<sf::Vector2i> occupied;
					for (auto cell : quads)
					{
						int cx = cell.x, cy = cell.y;
						if (!mgrid.isInBounds(cx, cy)) continue;
						mgrid.setBlocked(ix, iy, true);
						occupied.push_back(cell);
					}
					auto* Tower = new TowerBase("Base");
					Tower->Init();
					Tower->SetOccupiedCells(occupied);
					Tower->SetPosition(snapped);
					Tower->Reset();
					AddGameObject(Tower);
					towerList.push_back(Tower);

					auto* tower1 = new Tower1("Base1");
					tower1->Init();
					tower1->SetOccupiedCells(occupied);
					tower1->SetPosition(snapped);
					tower1->Reset();
					tower1->SetMonsters(monsterList);
					AddGameObject(tower1);

					isPlacingWall2 = false;
				}
			}
		}
		if (isPlacingWall3)
		{
			if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
			{
				if (world.x > 23.f && world.x < 670.f &&
					world.y > 320.f && world.y < 690.f)
				{

					float cw = mgrid.getCellSize().x;
					float ch = mgrid.getCellSize().y;
					int ix = int(std::round(world.x / cw));
					int iy = int(std::round(world.y / ch));


					std::array<sf::Vector2i, 4> quads = { {
						{ix - 1, iy - 1},
						{ ix , iy - 1},
						{ix - 1,  iy },
						{ ix ,  iy }
					} };

					std::vector<sf::Vector2i> occupied;
					for (auto cell : quads)
					{
						int cx = cell.x, cy = cell.y;
						if (!mgrid.isInBounds(cx, cy)) continue;
						mgrid.setBlocked(ix, iy, true);
						occupied.push_back(cell);
					}
					auto* Tower = new TowerBase("Base");
					Tower->Init();
					Tower->SetOccupiedCells(occupied);
					Tower->SetPosition(snapped);
					Tower->Reset();
					AddGameObject(Tower);
					towerList.push_back(Tower);

					auto* tower2 = new Tower2("Base1");
					tower2->Init();
					tower2->SetOccupiedCells(occupied);
					tower2->SetPosition(snapped);
					tower2->Reset();
					tower2->SetMonsters(monsterList);
					AddGameObject(tower2);

					isPlacingWall3 = false;
				}
			}
		}
	}
}

