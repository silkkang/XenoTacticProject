#pragma once
#include "GameObject.h"


class TileMap : public GameObject
{
protected:
    sf::VertexArray vertices;
    sf::Texture* texture = nullptr;

    std::string tilemapFile;
    std::string tilesetFile;


    int tileWidth = 0;
    int tileHeight = 0;
    int mapWidth = 0;
    int mapHeight = 0;

    std::vector<sf::Sprite> tiles;

public:
    TileMap(const std::string& name = "");
    ~TileMap() override = default;

    void Init() override;
    void Release() override;
    void Reset() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;

    bool Load(const std::string& mapFile, const std::string& tilesetFile, int firstGid = 1);

    void setScale(float x, float y);

};
