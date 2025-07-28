#include "stdafx.h"
#include "TowerBase.h"
#include "HitBox.h"

TowerBase::TowerBase(const std::string& name)
	: GameObject(name)
{
}

void TowerBase::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void TowerBase::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void TowerBase::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void TowerBase::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void TowerBase::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void TowerBase::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	texId = "graphics/towerbase.png";
	sf::Texture& tex = TEXTURE_MGR.Get(texId);
	body.setTexture(tex);
	body.setScale(1.40f, 1.95f);
	SetOrigin(Origins::MC);
	
}

void TowerBase::Release()
{
}

void TowerBase::Reset()
{
}

void TowerBase::Update(float dt)
{
	hitBox.UpdateTransform(body, GetLocalBounds());
}

void TowerBase::Draw(sf::RenderWindow& window)
{ 
	//std::cout << "ÀÌ¹ÌÁö" << std::endl;
	window.draw(body);
	hitBox.Draw(window);
}