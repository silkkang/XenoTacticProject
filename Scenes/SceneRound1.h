#pragma once
#include "Scene.h"
#include "TileMap.h"
#include "ResourceMgr.h" 
#include <SFML/Graphics.hpp>

class TileMap;
class Monster;

class SceneRound1 : public Scene
{
protected:
	TileMap* tileMap = nullptr;

	sf::Sprite uiSprite;
	sf::Sprite BackgroundSprite;

	std::list<Monster*> monsterList;
	std::list<Monster*> monsterPool;
public:
	

	SceneRound1();
	virtual ~SceneRound1() = default;


	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void Release() override;
	void MonsterSpawn(int count);
};

