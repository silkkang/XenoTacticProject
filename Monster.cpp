#include "stdafx.h"
#include "Monster.h"
#include "AnimationClip.h"

Monster::Monster(const std::string& name)
	: GameObject(name)
{
}

void Monster::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Monster::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Monster::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Monster::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Monster::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Monster::Init()
{
	
	body.setTexture(TEXTURE_MGR.Get("graphics/monster.png"));
	Utils::SetOrigin(body, Origins::BC);

	animator.SetTarget(&body);
	
}

void Monster::Release()
{
}

void Monster::Reset()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	hp = maxHp;
	
	animator.Play("animations/monsterCol1.csv");
	SetOrigin(Origins::BC);

}

void Monster::Update(float dt)
{
	

	position.x += speed * dt;
	body.setPosition(position);

	animator.Update(dt);

	
}

void Monster::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

