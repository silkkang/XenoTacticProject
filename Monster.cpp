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
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	std::string clipId = "monsterCol1";
	

	sprite.setTexture(TEXTURE_MGR.Get("graphics/monster.png"));

	animator.SetTarget(&sprite);
	animator.Play(clipId);

}

void Monster::Release()
{
}

void Monster::Reset()
{
	hp = maxHp;


	animator.Play("monsterCol1");
}

void Monster::Update(float dt)
{

	animator.Update(dt);
}

void Monster::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

