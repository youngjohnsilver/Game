//
//  animationloader.h
//  Game
//
//  Created by John Theiss on 7/21/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#ifndef Game_animationloader_h
#define Game_animationloader_h

// Standard dependencies
#include <map>
#include <memory>
#include <string>

// TinyXML2 dependencies
#include "tinyxml2.h"

// Forward declarations
class CAnimation;

class CAnimationLoader
{
public:
    CAnimationLoader();
    
    std::shared_ptr<CAnimation> Load(const std::string & animationFileName);
    
private:
    void LoadFrame(tinyxml2::XMLElement * element);
    void LoadSequence(tinyxml2::XMLElement * element);
    
    void BuildAnimationLoadActions();

private:
    std::shared_ptr<CAnimation> m_spAnimation;
    
    std::map<std::string, std::function<void(tinyxml2::XMLElement *)>> m_animationLoadActions;
};

#endif
