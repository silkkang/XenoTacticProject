#include "stdafx.h"
#include "Grid.h"

Grid::Grid(const sf::Vector2f& cellSize, const sf::Vector2u& gridCount)
	: mcellSize(cellSize), mgridCount(gridCount), mlines(sf::Lines)
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


