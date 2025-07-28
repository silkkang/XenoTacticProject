#include "stdafx.h"
#include "Tower6.h"
#include "AnimationClip.h"
#include "SceneRound1.h"
#include "Monster.h"
#include "HitBox.h"
#include <cmath>
Tower6::Tower6(const std::string& name)
	: GameObject(name)
{
}

void Tower6::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Tower6::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Tower6::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Tower6::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Tower6::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Tower6::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	texId = "tower6/1.png";
	sf::Texture& tex = TEXTURE_MGR.Get(texId);
	body.setTexture(tex);
	body.setScale(1.40f, 1.95f);
	SetOrigin(Origins::MC);

}

void Tower6::Release()
{
}

void Tower6::Reset()
{
}

void Tower6::Update(float dt)
{
	Monster* monster = nullptr;
	float distance = monsterRange * monsterRange;
	sf::Vector2f pos = GetPosition();

	for (auto* mo : *mMonsters)
	{
		if (!mo->GetActive()) continue;
		sf::Vector2f d = mo->GetPosition() - pos;
		float dist2 = d.x * d.x + d.y * d.y;
		if (dist2 < distance)
		{
			distance = dist2;
			monster = mo;
		}
	}

	if (monster)
	{
		sf::Vector2f dir = monster->GetPosition() - pos;
		float angle = std::atan2(dir.y, dir.x) * 180 / 3.14159265f;
		SetRotation(angle);
		mFireTimer += dt;
		if (monster->GetActive() && mFireTimer >= mFireRate)
		{
			monster->SetHit(mDamage);
			mFireTimer = 0.f;
			//monster->SetActive(false);
			//mScene->AddKillCount(1);
		}
	}

	hitBox.UpdateTransform(body, GetLocalBounds());
}

void Tower6::Draw(sf::RenderWindow& window)
{
	//std::cout << "ÀÌ¹ÌÁö" << std::endl;
	window.draw(body);
	hitBox.Draw(window);
}