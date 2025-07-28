#include "stdafx.h"
#include "TowerWall.h"
#include "AnimationClip.h"
#include "SceneRound1.h"
#include "Monster.h"
#include <cmath>
TowerWall::TowerWall(const std::string& name)
	: GameObject(name)
{
}

void TowerWall::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void TowerWall::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void TowerWall::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void TowerWall::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void TowerWall::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void TowerWall::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	texId = "wall/1.png";
	sf::Texture& tex = TEXTURE_MGR.Get(texId);
	body.setTexture(tex);
	body.setScale(1.40f, 1.95f);
	SetOrigin(Origins::MC);

}

void TowerWall::Release()
{
}

void TowerWall::Reset()
{
}

void TowerWall::Update(float dt)
{

	hitBox.UpdateTransform(body, GetLocalBounds());
}

void TowerWall::Draw(sf::RenderWindow& window)
{
	//std::cout << "ÀÌ¹ÌÁö" << std::endl;
	window.draw(body);
	hitBox.Draw(window);
}