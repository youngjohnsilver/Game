//
//  gamelevel.h
//  Game
//
//  Created by John Theiss on 7/25/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#ifndef Game_gamelevel_h
#define Game_gamelevel_h

// Standard dependencies
#include <memory>
#include <string>
#include <vector>

// Project dependencies
#include "boundingbox.h"

// Forward declarations
class CGameTile;

class CGameLevel
{
public:
    CGameLevel(
        const std::string & name,
        const int width,
        const int height,
        const std::vector<std::vector<std::shared_ptr<CGameTile>>> & layers,
        const std::vector<std::shared_ptr<SBoundingBox>> & collisionData);
    CGameLevel() = default;
    ~CGameLevel() = default;
    
    int GetWidth()const;
    int GetHeight()const;
    const std::vector<std::vector<std::shared_ptr<CGameTile>>> & GetLayers()const;
    const std::vector<std::shared_ptr<SBoundingBox>> & GetCollisionData()const;
    
    void SetName(const std::string & name) {m_name = name;}
    void SetWidth(const int width) {m_width = width;}
    void SetHeight(const int height) {m_height = height;}
    void SetLayers(const std::vector<std::vector<std::shared_ptr<CGameTile>>> & layers) {m_layers = layers;}
    void SetCollisionData(const std::vector<std::shared_ptr<SBoundingBox>> & collisionData)
        {m_collisionData = collisionData;}
    
    void AddLayer(const std::vector<std::shared_ptr<CGameTile>> layer) {m_layers.push_back(layer);}
    
private:
    std::string m_name;
    int m_width;
    int m_height;
    std::vector<std::vector<std::shared_ptr<CGameTile>>> m_layers;
    std::vector<std::shared_ptr<SBoundingBox>> m_collisionData;
};

#endif
