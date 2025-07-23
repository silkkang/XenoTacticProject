#pragma once
#include "GameObject.h"
#include "SceneRound1.h"
#include "Animator.h"
#include <SFML/Graphics.hpp>

class Monster : public GameObject
{
public:
	enum class Types
	{
		Monster1,
		Monster2,
		Monster3,
	};
	static const int TotalTypes = 3;
protected:
	sf::Sprite body;

	Types type = Types::Monster1;

	int maxHp = 0;
	int speed = 0;
	int damage = 1;
	int hp;

	Animator animator;
	std::string texId;
	int cols = 1;
	int rows = 1;
	float frameDuration = 0.1f;


public:
	Monster(const std::string& name = "");
	virtual ~Monster() = default;

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


	void SetType(Types type);

	sf::FloatRect GetLocalBounds() const override
	{
		return body.getLocalBounds();
	}

	sf::FloatRect GetGlobalBounds() const override
	{
		return body.getGlobalBounds();
	}
};

