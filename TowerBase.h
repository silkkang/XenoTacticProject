#pragma once
#include "GameObject.h"
#include "HitBox.h"

class TowerBase :
    public GameObject
{
protected:
	sf::Sprite body;
	HitBox hitBox;
	std::string texId;
public:
	TowerBase(const std::string& name = "");
	virtual ~TowerBase() = default;

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

	sf::FloatRect GetLocalBounds() const override
	{
		return body.getLocalBounds();
	}

	sf::FloatRect GetGlobalBounds() const override
	{
		return body.getGlobalBounds();
	}
};

