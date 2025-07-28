#pragma once
#include "Scene.h"
#include "TileMap.h"
#include "ResourceMgr.h" 
#include "Grid.h"
#include <SFML/Graphics.hpp>
#include "RoundMgr.h"

class TileMap;
class Monster;
class TowerBase;
class Tower1;
class Tower2;
class TowerWall;

class SceneRound1 : public Scene
{
protected:
	TileMap* tileMap = nullptr;
	Grid mgrid;
	std::vector<TowerBase*> towerList;
	RoundMgr mRoundMgr{};
	
	sf::Sprite uiSprite;
	sf::Sprite BackgroundSprite;
	sf::Sprite PickImageSprite;
	sf::Sprite PickImagexSprite;
	std::vector<Monster*> monsterList;
	std::vector<Monster*> monsterPool;

	float monsterTimer = 0;
	sf::RenderWindow& m_window;
	bool isPlacingWall1 = false;
	bool isPlacingWall2 = false;
	bool isPlacingWall3 = false;
	bool isPlacingWall4 = false;
	bool isPlacingWall5 = false;
	bool isPlacingWall6 = false;
	bool isPlacingWall7 = false;

	sf::Sprite wallSprite;
	bool isColliding = false;
	bool towerColliding = false;
	bool monsterColliding = false;

	int round = 0;
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

