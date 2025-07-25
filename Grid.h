#pragma once
#include <SFML/Graphics.hpp>

class Grid
{
protected:
	sf::Vector2f mcellSize;
	sf::Vector2u mgridCount;
	sf::VertexArray mlines;
	
public:
	Grid(const sf::Vector2f& cellSize, const sf::Vector2u& gridCount);
	void draw(sf::RenderTarget& target) const ;
	void draw(sf::RenderTarget& target, const sf::Transform& t) const;
	sf::Vector2f snapPosition(const sf::Vector2f& worldPos) const;
};

