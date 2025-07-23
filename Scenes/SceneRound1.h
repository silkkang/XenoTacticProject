#pragma once
#include "Scene.h"
#include "TileMap.h"

class TileMap;

class SceneRound1 : public Scene
{
protected:
	TileMap* tileMap = nullptr;

public:
	

	SceneRound1();
	virtual ~SceneRound1() = default;


	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void Release() override;
};

