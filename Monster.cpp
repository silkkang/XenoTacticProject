#include "stdafx.h"
#include "Monster.h"
#include "AnimationClip.h"
#include "SceneRound1.h"
#include "TowerBase.h"
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
		sf::Vector2f direction = { delta.x / distance, delta.y / distance };
		sf::Vector2f step = direction * (speed * dt);
		sf::Vector2f nextPos = nowpos + step;

		if (nextPos.x < -50 || nextPos.x > 1280 || nextPos.y < 326 )
		{
			
			std::cout << "¸Ê À§¿¡ ´ê¾Æ.\n";
			StartDodge(-20.f);
			return;
		}
	
		if (nextPos.x < -50 || nextPos.x > 1280 || nextPos.y > 700)
		{
		
			std::cout << "¸Ê ¹ÛÀ¸·Î ³ª°¡ ¸ØÃä´Ï´Ù.\n";

			return;
		}
		if (isDodging)
		{
			
			float dy = speed * dt;
			nowpos.y = std::max(nowpos.y - dy, dodgeTargetY);
			SetPosition(nowpos);


			if (nowpos.y <= dodgeTargetY)
			{
				isDodging = false;

			}
			return;
		}
		if (distance < 20)
		{
			body.setPosition(arrivePos);
			isArrive = false;
			SetActive(false);
			//ÇÃ·¹ÀÌ¾î hp -= 1;
			return;
		}
		else
		{
		

			if (mTowers)
			{
				for (auto* tower : *mTowers)
				{
					if (GetGlobalBounds().intersects(tower->GetGlobalBounds()))
					{
						std::cout << "¸ó½ºÅÍ°¡ Å¸¿ö¿Í Ãæµ¹ÇØ ¸Ê±âÁØ À§·Î°©´Ï´Ù.\n";
						StartDodge(20.f);
						return;          
					}
				}
			}
			/*else
			{
				auto cellsize = mgrid->getCellSize();
				float step = cellsize.x;
				sf::Vector2f leftDirection = { -direction.y, direction.x };
				sf::Vector2f dodgeOffset = leftDirection * (step * 2.f);
				sf::Vector2f dodgeWorld = nowpos + dodgeOffset;

				
			

				auto [lcx, lcy] = mgrid->worldToCell(dodgeWorld);
				if (mgrid->isInBounds(lcx, lcy) && !mgrid->isBlocked(lcx, lcy))
				{
					
					sf::Vector2f center = mgrid->cellToWorld(lcx, lcy) + cellsize * 0.5f;
					SetPosition(center);
				}
				else
				{
					sf::Vector2f rightDirection = { direction.y, -direction.x };
				}
			}*/

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

void Monster::SetHit(int d)
{
	hp -= d;
	std::cout << hp << d << std::endl;
		if (hp <= 0)
	{
		SetActive(false);
	}
}

