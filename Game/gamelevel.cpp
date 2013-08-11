//
//  gamelevel.cpp
//  Game
//
//  Created by John Theiss on 7/25/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#include "gamelevel.h"

//
// Constructor
//
CGameLevel::CGameLevel(
    const std::string & name,
    const int width,
    const int height,
    const std::vector<std::vector<std::shared_ptr<CGameTile>>> & layers,
    const std::vector<std::shared_ptr<SBoundingBox>> & collisionData) :
        m_name(name),
        m_width(width),
        m_height(height),
        m_layers(layers),
        m_collisionData(collisionData)
{
}

//
// Accessors
//
int CGameLevel::GetWidth()const
{
    return m_width;
}

int CGameLevel::GetHeight()const
{
    return m_height;
}

const std::vector<std::vector<std::shared_ptr<CGameTile>>> & CGameLevel::GetLayers()const
{
    return m_layers;
}

const std::vector<std::shared_ptr<SBoundingBox>> & CGameLevel::GetCollisionData()const
{
    return m_collisionData;
}

