#include "stdafx.h"
#include "Grid.h"

Grid::Grid(const sf::Vector2f& cellSize, const sf::Vector2u& gridCount)
	: mcellSize(cellSize), mgridCount(gridCount), mlines(sf::Lines),mblocked(gridCount.x*gridCount.y,false)
{
	sf::Color col(200, 200, 200, 100);
	for (unsigned x = 0; x < gridCount.x; ++x)
	{
		float xp = x * cellSize.x;
		mlines.append({ {xp, 0}, col });
		mlines.append({ {xp, float(gridCount.y) * cellSize.y}, col });
	}
	for (unsigned y = 0; y < gridCount.y; ++y)
	{
		float yp = y * cellSize.y;
		mlines.append(sf::Vertex(sf::Vector2f(0.f, yp), col));
		mlines.append(sf::Vertex(sf::Vector2f(gridCount.x * cellSize.x, yp), col));

	}
}
void Grid::draw(sf::RenderTarget& target) const
{
	target.draw(mlines);
}

void Grid::draw(sf::RenderTarget& target, const sf::Transform& t) const
{
	target.draw(mlines, sf::RenderStates(t));
}

sf::Vector2f Grid::snapPosition(const sf::Vector2f& worldPos) const
{
	int gx = static_cast<int>(std::round(worldPos.x / mcellSize.x));
	int gy = static_cast<int>(std::round(worldPos.y / mcellSize.y));
	return { gx * mcellSize.x, gy * mcellSize.y };
}

std::pair<int, int> Grid::worldToCell(const sf::Vector2f& worldPos) const
{
	int x = static_cast<int>(worldPos.x / mcellSize.x);
	int y = static_cast<int>(worldPos.y / mcellSize.y);
	x = std::clamp(x, 0, int(mgridCount.x) - 1);
	y = std::clamp(y, 0, int(mgridCount.y) - 1);
	return { x, y };
}

sf::Vector2f Grid::cellToWorld(int cx, int cy) const
{
	return { cx * mcellSize.x, cy * mcellSize.y };
}

void Grid::setBlocked(int cx, int cy, bool blocked) 
{
	
	if (cx < 0 || cx >= int(mgridCount.x) ||
		cy < 0 || cy >= int(mgridCount.y))
	{
		
		return;
	}
	mblocked[cy * mgridCount.x + cx] = blocked;
}

bool Grid::isBlocked(int cx, int cy) const
{
	if (cx < 0 || cx >= int(mgridCount.x) ||
		cy < 0 || cy >= int(mgridCount.y)) 
		return true;
		return mblocked[cy * mgridCount.x + cx];

}

bool Grid::isBlocked(const sf::Vector2f& worldPos) const
{
	auto [cx, cy] = worldToCell(worldPos);
	return isBlocked(cx, cy);
}

bool Grid::isInBounds(int cx, int cy) const
{
	return cx >= 0&& cx< int(mgridCount.x)
		&& cy >= 0 && cy< int(mgridCount.y);
}


