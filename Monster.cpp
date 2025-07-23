#include "stdafx.h"
#include "Monster.h"

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


	AnimationClip clip;
	clip.setId("monster_move");
	clip.setFps(4);
	clip.setLoopType(AnimationLoopTypes::Loop);

	/*auto& tex = TEXTURE_MGR.Get("graphics / monster.png");
	int cols = 4;
	int raws = 2;
	int frameW = tex.getSize().x / cols;
	int frameH = tex.getSize().y / raws;
	for (int i = 0; i < cols; ++i)
	{
		for (int j = 0; j < raws; ++j)
		{
			sf::IntRect rect(i * frameW, j * frameH, frameW, frameH);
			clip.addFrame("monster_move");
		}
	}*/

	SetType(type);
}

void Monster::Release()
{
}

void Monster::Reset()
{
	hp = maxHp;
}

void Monster::Update(float dt)
{
}

void Monster::Draw(sf::RenderWindow& window)
{
}

void Monster::SetType(Types type)
{
	this->type = type;
	switch (this->type)
	{
		case Types::Monster1:
			texId = "";
			maxHp = 200;
			speed = 50;
			damage = 1;
			break;
	/*case Types::Monster2:
			texId = "";
			maxHp = 200;
			speed = 50;
			damage = 1;
			break;*/
	}
}
