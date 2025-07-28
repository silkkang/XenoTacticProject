#pragma once
#include "GameObject.h"
#include "HitBox.h"
#include "towerBase.h"
#include "SceneRound1.h"
class Tower2 :
	public GameObject
{
protected:
	sf::Sprite body;
	HitBox hitBox;
	std::string texId;

	std::vector<sf::Vector2i> mOccupiedCells;

	const std::vector<Monster*>* mMonsters = nullptr;
	float monsterRange = 200.f;
	float mFireRate = 2.0f;
	float mFireTimer = 0.0f;
	int mDamage = 50;
public:
	Tower2(const std::string& name = "");
	virtual ~Tower2() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void SetMonsters(const std::vector<Monster*>& monsters)
	{
		mMonsters = &monsters;
	}
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	sf::FloatRect GetLocalBounds() const override
	{
		return body.getLocalBounds();
	}

	sf::FloatRect GetGlobalBounds() const override
	{
		return body.getGlobalBounds();
	}

	void SetOccupiedCells(const std::vector<sf::Vector2i>& cells)
	{
		mOccupiedCells = cells;
	}

	const std::vector<sf::Vector2i>& GetOccupiedCells() const
	{
		return mOccupiedCells;
	}
};

