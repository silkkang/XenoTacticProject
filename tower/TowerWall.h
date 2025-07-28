#pragma once
#include "GameObject.h"
#include "HitBox.h"
#include "towerBase.h"
#include "SceneRound1.h"
class TowerWall :
	public GameObject
{
protected:
	sf::Sprite body;
	HitBox hitBox;
	std::string texId;

	std::vector<sf::Vector2i> mOccupiedCells;


public:
	TowerWall(const std::string& name = "");
	virtual ~TowerWall() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;


	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;


};

