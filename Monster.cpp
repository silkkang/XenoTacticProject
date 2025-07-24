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

void Monster::SetArrivePos(const sf::Vector2f& pos)
{
	arrivePos = pos;
	isArrive = true;
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
	if (isArrive)
	{
		sf::Vector2f nowpos = GetPosition();
		sf::Vector2f delta = arrivePos - nowpos;
		float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);


		if (distance < 20)
		{
			body.setPosition(arrivePos);
			isArrive = false;
			SetActive(false);
		}
		else
		{
			sf::Vector2f direction = { delta.x / distance, delta.y / distance };
			float moveStep = speed * dt;
			sf::Vector2f offset = direction * moveStep;
			sf::Vector2f nextPos = nowpos + offset;
			SetPosition(nextPos);

			float angleRad = std::atan2(direction.y, direction.x);
			float angleDeg = angleRad * 180.f / 3.14159265f;
			body.setRotation(angleDeg);
		}
	}

	animator.Update(dt);
	hitBox.UpdateTransform(body, GetLocalBounds());

	
}

void Monster::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);

}

