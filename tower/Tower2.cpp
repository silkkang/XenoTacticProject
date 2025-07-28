#include "stdafx.h"
#include "Tower2.h"
#include "AnimationClip.h"
#include "SceneRound1.h"
#include "Monster.h"
#include "HitBox.h"
#include <cmath>
Tower2::Tower2(const std::string& name)
	: GameObject(name)
{
}

void Tower2::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Tower2::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Tower2::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Tower2::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Tower2::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Tower2::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	texId = "tower2/1.png";
	sf::Texture& tex = TEXTURE_MGR.Get(texId);
	body.setTexture(tex);
	body.setScale(1.40f, 1.95f);
	SetOrigin(Origins::MC);

}

void Tower2::Release()
{
}

void Tower2::Reset()
{
}

void Tower2::Update(float dt)
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

void Tower2::Draw(sf::RenderWindow& window)
{
	//std::cout << "ÀÌ¹ÌÁö" << std::endl;
	window.draw(body);
	hitBox.Draw(window);
}