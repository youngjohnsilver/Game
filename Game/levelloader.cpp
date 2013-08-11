//
//  levelloader.cpp
//  Game
//
//  Created by John Theiss on 7/25/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#include "levelloader.h"

// TinyXML2 dependencies
#include "tinyxml2.h"

// Project dependencies
#include "gameassert.h"
#include "gameimage.h"
#include "gamelevel.h"

using N_GameAssert::GameAssert;

namespace
{

const std::string LAYER_TOKEN("layer");
const std::string OBJECT_TOKEN("objectgroup");
const std::string COLLISION_BOXES_TOKEN("CollisionBoxes");

}

//
// Constructor
//
CLevelLoader::CLevelLoader()
{
    BuildCharacterLoadActions();
}

//
// Load objects
//
void CLevelLoader::LoadObjects(tinyxml2::XMLElement * element)
{
    GameAssert(nullptr != element, "Null element passed to CLevelLoader::LoadObjects");

    if(COLLISION_BOXES_TOKEN == element->Attribute("name"))
    {
        LoadCollisionData(element);
    }
    else
    {
        std::vector<std::shared_ptr<CGameTile>> objectLayer;
        tinyxml2::XMLElement * nextElement = element->FirstChildElement();

        while(nullptr != nextElement)
        {
            int tileID = nextElement->IntAttribute("gid");
            int worldX = nextElement->IntAttribute("x");
            int worldY = nextElement->IntAttribute("y");
            worldY -= m_tileData.m_height;
            if(tileID != 0)
            {
                CPoint2D<int> worldPosition(worldX, worldY);
                CPoint2D<int> tileSetPosition = ConvertTileIDToTileSetPosition(tileID);
                std::shared_ptr<CGameTile> tile = std::make_shared<CGameTile>(
                    m_tileData,
                    tileID,
                    worldPosition,
                    tileSetPosition);
                objectLayer.push_back(tile);
            }
            nextElement =  nextElement->NextSiblingElement();
        }
        m_spLevel->AddLayer(objectLayer);
    }
}

//
// Load collision data
//
void CLevelLoader::LoadCollisionData(tinyxml2::XMLElement * element)
{
    GameAssert(nullptr != element, "Null element passed to CLevelLoader::LoadCollisionData");
    
    std::vector<std::shared_ptr<SBoundingBox>> boxes;
    
    tinyxml2::XMLElement * nextElement = element->FirstChildElement();
    while(nullptr != nextElement)
    {
        std::shared_ptr<SBoundingBox> spNewBox = std::make_shared<SBoundingBox>();
        spNewBox->m_position.X() = nextElement->IntAttribute("x");
        spNewBox->m_position.Y() = nextElement->IntAttribute("y");
        spNewBox->m_width = nextElement->IntAttribute("width");
        spNewBox->m_height = nextElement->IntAttribute("height");
        
        spNewBox->m_position.X() += spNewBox->m_width / 2;
        spNewBox->m_position.Y() += spNewBox->m_height / 2;
        boxes.push_back(spNewBox);

        nextElement = nextElement->NextSiblingElement();
    }
    m_spLevel->SetCollisionData(boxes);
}

//
// Convert a tileID into a tile set width and height
//
CPoint2D<int> CLevelLoader::ConvertTileIDToTileSetPosition(const int tileID)const
{
    int relativeID = tileID - m_firstTileID;
    int numTilesWide = m_tileSetWidth / m_tileData.m_width;
    
    int positionX = (relativeID % numTilesWide)*m_tileData.m_width;
    int positionY = (relativeID/numTilesWide)*m_tileData.m_height;
    CPoint2D<int> position(positionX, positionY);
    return position;
}

//
// Load a level layer
//
void CLevelLoader::LoadLayer(tinyxml2::XMLElement * element)
{
    GameAssert(nullptr != element, "Null element passed to CLevelLoader::LoadLayer");
    
    GameAssert(
        nullptr != element->FirstChildElement(),
        "No data element in element passed to CLevelLoader::LoadLayer");
    
    std::vector<std::shared_ptr<CGameTile>> layer;
    tinyxml2::XMLElement * nextElement = element->FirstChildElement()->FirstChildElement();
    int worldX = 0;
    int worldY = 0;
    while(nullptr != nextElement)
    {
        int tileID = nextElement->IntAttribute("gid");
        if(tileID != 0)
        {
            CPoint2D<int> worldPosition(worldX, worldY);
            CPoint2D<int> tileSetPosition = ConvertTileIDToTileSetPosition(tileID);
            std::shared_ptr<CGameTile> tile = std::make_shared<CGameTile>(
                m_tileData,
                tileID,
                worldPosition,
                tileSetPosition);
            layer.push_back(tile);
        }
        worldX += m_tileData.m_width;
        if(worldX >= m_spLevel->GetWidth())
        {
            worldX = 0;
            worldY += m_tileData.m_height;
        }
        nextElement =  nextElement->NextSiblingElement();
    }
    m_spLevel->AddLayer(layer);
}

//
// Create the action map
//
void CLevelLoader::BuildCharacterLoadActions()
{
    using namespace std::placeholders;
    m_levelLoadActions =
    {
        {LAYER_TOKEN, std::bind(&CLevelLoader::LoadLayer, this, _1)},
        {OBJECT_TOKEN, std::bind(&CLevelLoader::LoadObjects, this, _1)}
    };
}

//
// Load a level from a file
//
std::shared_ptr<CGameLevel> CLevelLoader::Load(const std::string & levelFileName)
{
    m_spLevel = std::make_shared<CGameLevel>();
    tinyxml2::XMLDocument levelDocument;
    levelDocument.LoadFile(levelFileName.c_str());
    
    tinyxml2::XMLElement * mapElement = levelDocument.LastChildElement();
    std::string errorMessage("No map element in level file: ");
    errorMessage += levelFileName;
    GameAssert(nullptr != mapElement, errorMessage);
    
    m_tileData.m_width = mapElement->IntAttribute("tilewidth");
    m_tileData.m_height = mapElement->IntAttribute("tileheight");
    
    int numTilesWide = mapElement->IntAttribute("width");
    int numTilesHigh = mapElement->IntAttribute("height");
    
    m_spLevel->SetWidth(numTilesWide * m_tileData.m_width);
    m_spLevel->SetHeight(numTilesHigh * m_tileData.m_height);
    
    tinyxml2::XMLElement * tileSetElement = mapElement->FirstChildElement();
    errorMessage = std::string("No tileset element in level file: ");
    errorMessage += levelFileName;
    GameAssert(nullptr != tileSetElement, errorMessage);
    
    m_firstTileID = tileSetElement->IntAttribute("firstgid");
    
    tinyxml2::XMLElement * imageElement = tileSetElement->FirstChildElement();
    errorMessage = std::string("No image element in level file: ");
    errorMessage += levelFileName;
    GameAssert(nullptr != imageElement, errorMessage);
    
    m_tileSetWidth = imageElement->IntAttribute("width");
    m_tileSetHeight = imageElement->IntAttribute("height");
    std::string imgFileName("LevelData/");
    imgFileName += imageElement->Attribute("source");
    
    m_tileData.m_tileSet = std::make_shared<CGameImage>();
    m_tileData.m_tileSet->LoadImage(imgFileName);

    tinyxml2::XMLElement * nextElement = tileSetElement->NextSiblingElement();
    while(nullptr != nextElement)
    {
        m_levelLoadActions.at(nextElement->Name())(nextElement);
        nextElement = nextElement->NextSiblingElement();
    }
    
    return m_spLevel;
}
