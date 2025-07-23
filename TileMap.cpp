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
    for (auto& spr : tiles)
        window.draw(spr);
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
    tiles.clear();
    while (std::getline(ss, line, ','))
    {
        int gid = std::stoi(line);
        if (gid >= firstGid)
        {
            int index = gid - firstGid;
            int tu = index % (texture->getSize().x / tileWidth);
            int tv = index / (texture->getSize().x / tileWidth);

            sf::Sprite spr;
            spr.setTexture(*texture);
            spr.setTextureRect(
                {
                tu * tileWidth,tv * tileHeight,
                tileWidth,tileHeight
                });
            spr.setPosition(
                static_cast<float>(x * tileWidth),
                static_cast<float>(y * tileHeight)
            );
            tiles.push_back(std::move(spr));
        }
        if (++x >= mapWidth) { x = 0; ++y; }
    }

    return true;
}


void TileMap::setScale(float x, float y)
{
  for (auto& spr : tiles)
  {
    spr.setScale(x, y);
  }
}

