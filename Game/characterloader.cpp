//
//  characterloader.cpp
//  Game
//
//  Created by John Theiss on 7/20/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#include "characterloader.h"

// Standard dependencies
#include <exception>
#include <fstream>
#include <map>

// Project dependencies
#include "animation.h"
#include "animationframe.h"
#include "characterview.h"
#include "commonloader.h"
#include "gameassert.h"
#include "gameimage.h"
#include "point2d.h"

using N_GameAssert::GameAssert;

// Helpers
namespace
{

const std::string IMAGE_LAYERS_TOKEN("Layers");
const std::string IMAGE_TOKEN("image");
const std::string ANIMATION_TOKEN("animation");
const std::string ANIMATIONS_TOKEN("Animations");
const std::string POSITION_TOKEN("Position");

}

//
// Constructor
//
CCharacterLoader::CCharacterLoader()
{
    BuildCharacterLoadActions();
}

//
// Create a map of tokens to functions that are acceptable
// during LoadCharacter
//
void CCharacterLoader::BuildCharacterLoadActions()
{
    using namespace std::placeholders;
    m_characterLoadActions =
    {
        {IMAGE_LAYERS_TOKEN, std::bind(&CCharacterLoader::LoadImageLayers, this, _1)},
        {POSITION_TOKEN, std::bind(&CCharacterLoader::LoadCharacterPosition, this, _1)},
        {ANIMATIONS_TOKEN, std::bind(&CCharacterLoader::LoadAnimations, this, _1)}
    };
}

//
// Create a game image from an image file
//
void CCharacterLoader::LoadImageLayers(tinyxml2::XMLElement * element)
{
    GameAssert(nullptr != element, "Empty element passed to CCharacterLoader::LoadImageLayers");
    
    tinyxml2::XMLElement * nextElement(element->FirstChildElement());
    while(nullptr != nextElement)
    {
        std::string imageFileName = nextElement->Attribute(IMAGE_TOKEN.c_str());
        std::shared_ptr<CGameImage> spImage = std::make_shared<CGameImage>();
        spImage->LoadImage(imageFileName);
        m_data->m_characterLayers.push_back(spImage);
        nextElement = nextElement->NextSiblingElement();
    }
}

//
// Load the start position for the character
//
void CCharacterLoader::LoadCharacterPosition(tinyxml2::XMLElement * element)
{
    GameAssert(nullptr != element, "Empty element passed to CCharacterLoader::LoadPosition");

    CPoint2D<int> point;
    point.X() = element->IntAttribute("X");
    point.Y() = element->IntAttribute("Y");
    m_data->m_position = point;
    m_data->m_zLevel = element->IntAttribute("Z");
}

//
// Load an animation file
//
void CCharacterLoader::LoadAnimations(tinyxml2::XMLElement * element)
{
    GameAssert(nullptr != element, "Empty element passed to CCharacterLoader::LoadAnimations");
    
    tinyxml2::XMLElement * nextElement = element->FirstChildElement();
    while(nullptr != nextElement)
    {
        std::string animationFileName = nextElement->Attribute(ANIMATION_TOKEN.c_str());
        m_currentAnimation = N_CommonLoader::LoadAnimation(animationFileName);
        m_data->m_animations[m_currentAnimation->GetName()] = m_currentAnimation;
        nextElement = nextElement->NextSiblingElement();
    }
}

//
// Load a character from a file
//
std::shared_ptr<CCharacterView> CCharacterLoader::Load(const std::string & characterFileName)
{
    m_data.reset(new SCharacterViewData());

    tinyxml2::XMLDocument characterDocument;
    characterDocument.LoadFile(characterFileName.c_str());
    
    tinyxml2::XMLElement * characterElement = characterDocument.RootElement();
    GameAssert(nullptr != characterElement, "No Character element in CCharacterLoader::Load");

    tinyxml2::XMLElement * nextElement = characterElement->FirstChildElement();
    while(nullptr != nextElement)
    {
        m_characterLoadActions.at(nextElement->Name())(nextElement);
        nextElement = nextElement->NextSiblingElement();
    }
    
    std::shared_ptr<CCharacterView> spCharacter = std::make_shared<CCharacterView>(*m_data);
    
    return spCharacter;
}





