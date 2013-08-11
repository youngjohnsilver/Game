//
//  levelloader.h
//  Game
//
//  Created by John Theiss on 7/25/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#ifndef Game_levelloader_h
#define Game_levelloader_h

// Standard dependencies
#include <map>
#include <memory>

// TinyXML2 dependencies
#include "tinyxml2.h"

// Project dependencies
#include "gametile.h"

// Forward declarations
class CGameLevel;

class CLevelLoader
{
public:
    CLevelLoader();
    std::shared_ptr<CGameLevel> Load(const std::string & levelFileName);
    
private:
    void BuildCharacterLoadActions();
    void LoadLayer(tinyxml2::XMLElement * element);
    void LoadObjects(tinyxml2::XMLElement * element);
    void LoadCollisionData(tinyxml2::XMLElement * element);
    CPoint2D<int> ConvertTileIDToTileSetPosition(const int tileID)const;
    
private:
    std::shared_ptr<CGameLevel> m_spLevel;
    STileData m_tileData;
    int m_firstTileID;
    int m_tileSetWidth;
    int m_tileSetHeight;
    
    std::map<std::string, std::function<void(tinyxml2::XMLElement *)>> m_levelLoadActions;
};

#endif
