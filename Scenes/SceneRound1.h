#pragma once
#include "Scene.h"
#include "TileMap.h"
#include "ResourceMgr.h" 
#include "Grid.h"
#include <SFML/Graphics.hpp>

class TileMap;
class Monster;
class TowerBase;
class SceneRound1 : public Scene
{
protected:
	TileMap* tileMap = nullptr;

	sf::Sprite uiSprite;
	sf::Sprite BackgroundSprite;
	sf::Sprite PickImageSprite;
	sf::Sprite PickImagexSprite;
	std::vector<Monster*> monsterList;
	std::vector<Monster*> monsterPool;

	float monsterTimer = 0;
	sf::RenderWindow& m_window;
	Grid mgrid;
	bool isPlacingWall = false;
	sf::Sprite wallSprite;


public:
	

	SceneRound1(sf::RenderWindow& window);
	virtual ~SceneRound1() = default;


	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void Release() override;
	void MonsterSpawn(int count);
	void OnEvent(const sf::Event& ev) override;
};

