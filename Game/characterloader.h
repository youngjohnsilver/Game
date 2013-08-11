//
//  characterloader.h
//  Game
//
//  Created by John Theiss on 7/20/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#ifndef Game_characterloader_h
#define Game_characterloader_h

// Standard dependencies
#include <functional>
#include <map>
#include <memory>
#include <string>

// TinyXML dependencies
#include "tinyxml2.h"

// Forward declarations
class CAnimation;
class CAnimationFrame;
class CCharacterView;
struct SCharacterViewData;

class CCharacterLoader
{
public:
    CCharacterLoader();
    
    std::shared_ptr<CCharacterView> Load(const std::string & characterFileName);
    
private:
    void LoadImageLayers(tinyxml2::XMLElement * element);
    void LoadCharacterPosition(tinyxml2::XMLElement * element);
    void LoadAnimations(tinyxml2::XMLElement * element);
    
    void BuildCharacterLoadActions();
    
private:
    std::unique_ptr<SCharacterViewData> m_data;
    std::shared_ptr<CAnimation> m_currentAnimation;
    
    std::map<std::string, std::function<void(tinyxml2::XMLElement *)>> m_characterLoadActions;
};

#endif
