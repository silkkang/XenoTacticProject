#include "stdafx.h"
#include "TileMap.h"
#include "ResourceMgr.h"
#include "Utils.h"
#include "pugixml.hpp"

TileMap::TileMap(const std::string& name)
    : GameObject(name)
{
}

void TileMap::Init()
{
    sortingLayer = SortingLayers::Background;
    sortingOrder = 0;
}

void TileMap::Release()
{
}

void TileMap::Reset()
{
}

void TileMap::Update(float dt)
{
}

void TileMap::Draw(sf::RenderWindow& window)
{
    sf::RenderStates states = sf::RenderStates::Default;
    states.transform.translate(position).rotate(rotation).scale(scale);
    states.texture = texture;

    window.draw(vertices, states);
}

bool TileMap::Load(const std::string& mapFile, const std::string& tilesetFile, int firstGid)
{
    if (!TEXTURE_MGR.Exists(tilesetFile))
    {
        TEXTURE_MGR.Load(tilesetFile);
    }
    texture = &TEXTURE_MGR.Get(tilesetFile);

    pugi::xml_document doc;
    if (!doc.load_file(mapFile.c_str()))
        return false;

    auto mapNode = doc.child("map");
    mapWidth = mapNode.attribute("width").as_int();
    mapHeight = mapNode.attribute("height").as_int();
    tileWidth = mapNode.attribute("tilewidth").as_int();
    tileHeight = mapNode.attribute("tileheight").as_int();

    vertices.setPrimitiveType(sf::Quads);
    vertices.clear();

    auto layer = mapNode.find_child_by_attribute("layer", "name", "Tile Layer 1");
    if (!layer)
        return false;

    auto data = layer.child("data").text().as_string();

    std::stringstream ss(data);
    std::string line;
    int x = 0, y = 0;

    while (std::getline(ss, line, ','))
    {
        int gid = std::stoi(line);
        if (gid >= firstGid)
        {
            int texIndex = gid - firstGid;
            int tu = texIndex % (texture->getSize().x / tileWidth);
            int tv = texIndex / (texture->getSize().x / tileWidth);

            sf::Vertex quad[4];

            quad[0].position = sf::Vector2f(x * (float)tileWidth, y * (float)tileHeight);
            quad[1].position = sf::Vector2f((x + 1) * (float)tileWidth, y * (float)tileHeight);
            quad[2].position = sf::Vector2f((x + 1) * (float)tileWidth, (y + 1) * (float)tileHeight);
            quad[3].position = sf::Vector2f(x * (float)tileWidth, (y + 1) * (float)tileHeight);


            quad[0].texCoords = sf::Vector2f(tu * (float)tileWidth, tv * (float)tileHeight);
            quad[1].texCoords = sf::Vector2f((tu + 1) * (float)tileWidth, tv * (float)tileHeight);
            quad[2].texCoords = sf::Vector2f((tu + 1) * (float)tileWidth, (tv + 1) * (float)tileHeight);
            quad[3].texCoords = sf::Vector2f(tu * (float)tileWidth, (tv + 1) * (float)tileHeight);


            for (int i = 0; i < 4; ++i)
            {
                vertices.append(quad[i]);
            }
        }

        x++;
        if (x >= mapWidth)
        {
            x = 0;
            y++;
        }
    }

    return true;
}
