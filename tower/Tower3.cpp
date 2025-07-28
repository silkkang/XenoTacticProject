#include "stdafx.h"
#include "Tower3.h"
#include "AnimationClip.h"
#include "SceneRound1.h"
#include "Monster.h"
#include <cmath>
Tower3::Tower3(const std::string& name)
	: GameObject(name)
{
}

void Tower3::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Tower3::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Tower3::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Tower3::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Tower3::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Tower3::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	texId = "tower34/1.png";
	sf::Texture& tex = TEXTURE_MGR.Get(texId);
	body.setTexture(tex);
	body.setScale(1.40f, 1.95f);
	SetOrigin(Origins::MC);

}

void Tower3::Release()
{
}

void Tower3::Reset()
{
}

void Tower3::Update(float dt)
{

	hitBox.UpdateTransform(body, GetLocalBounds());
}

void Tower3::Draw(sf::RenderWindow& window)
{
	//std::cout << "ÀÌ¹ÌÁö" << std::endl;
	window.draw(body);
	hitBox.Draw(window);
}