#pragma once
#include <SFML/Graphics.hpp>

class Grid
{
protected:
	sf::Vector2f mcellSize;
	sf::Vector2u mgridCount;
	sf::VertexArray mlines;
	std::vector<bool> mblocked;
public:
	Grid(const sf::Vector2f& cellSize, const sf::Vector2u& gridCount);

	void draw(sf::RenderTarget& target) const ;
	void draw(sf::RenderTarget& target, const sf::Transform& t) const;
	sf::Vector2f snapPosition(const sf::Vector2f& worldPos) const;

	std::pair<int, int> worldToCell(const sf::Vector2f& worldPos) const;
	sf::Vector2f cellToWorld(int cx, int cy) const;

	void setBlocked(int cx, int cy, bool blocked =true) ; 
	bool isBlocked(int cx, int cy) const;
	bool isBlocked(const sf::Vector2f& worldPos) const;

	const sf::Vector2f& getCellSize() const { return mcellSize; }
	bool isInBounds(int cx, int cy) const;
};

