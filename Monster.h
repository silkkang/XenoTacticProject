#pragma once
#include "GameObject.h"
#include "SceneRound1.h"
#include "Animator.h"
#include <SFML/Graphics.hpp>
#include "HitBox.h"	
#include "Grid.h"
class Scene;

class Monster : public GameObject
{
protected:
	sf::Sprite body;
	Animator animator;

	int maxHp = 100;
	int speed = 50;
	int damage = 1;
	int hp;

	HitBox hitBox;

	std::string texId;
	int cols = 1;
	int rows = 1;
	float frameDuration = 0.1f;
	sf::Sprite sprite;
	
	sf::Vector2f arrivePos{ 0.f,0.f };
	bool isArrive = false;
	bool blocked = false;
	Scene* scene = nullptr;
	Grid* mgrid = nullptr;
	const std::vector<TowerBase*>* mTowers = nullptr;

	bool isDodging = false;
	float dodgeTargetY = 0.f;
	
public:
	Monster(const std::string& name = "");
	virtual ~Monster() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void SetArrivePos(const sf::Vector2f& pos);
	void SetGrid(Grid* g) { mgrid = g; }
	void SetTowers(const std::vector<TowerBase*>& towers) {mTowers = &towers;}
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	
	void SetHit(int d);
	

	void StartDodge(float targetY) {
		isDodging = true;
		dodgeTargetY = GetPosition().y-targetY;

		body.setRotation(-90.f);
	}

	sf::FloatRect GetLocalBounds() const override
	{
		return body.getLocalBounds();
	}

	sf::FloatRect GetGlobalBounds() const override
	{
		return body.getGlobalBounds();
	}
};

