//
//  animationloader.cpp
//  Game
//
//  Created by John Theiss on 7/21/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#include "animationloader.h"

// Standard dependencies
#include <sstream>

// TinyXML2 dependencies
#include "tinyxml2.h"

// Project dependencies
#include "animation.h"
#include "animationframe.h"
#include "gameassert.h"

using N_GameAssert::GameAssert;

namespace
{

const std::string NAME_TOKEN("name");
const std::string FRAME_RATE_TOKEN("framerate");
const std::string SEQUENCE_TOKEN("Sequence");
const std::string FRAME_TOKEN("Frame");
const std::string WIDTH_TOKEN("width");
const std::string HEIGHT_TOKEN("height");

}

//
// Constructor
//
CAnimationLoader::CAnimationLoader()
{
    BuildAnimationLoadActions();
}

//
// Build a map of tokens to actions for loading animations
//
void CAnimationLoader::BuildAnimationLoadActions()
{
    using namespace std::placeholders;
    m_animationLoadActions =
    {
        {FRAME_TOKEN, std::bind(&CAnimationLoader::LoadFrame, this, _1)},
        {SEQUENCE_TOKEN, std::bind(&CAnimationLoader::LoadSequence, this, _1)}
    };
}

//
// Load a frame from a file stream
//
void CAnimationLoader::LoadFrame(tinyxml2::XMLElement * element)
{
    GameAssert(nullptr != element, "Null element passed to CAnimationLoader::LoadFrame");

    CAnimationFrame frame;
    
    frame.SetWidth(element->IntAttribute(WIDTH_TOKEN.c_str()));
    frame.SetHeight(element->IntAttribute(HEIGHT_TOKEN.c_str()));

    tinyxml2::XMLElement * pointElement = element->LastChildElement();
    
    GameAssert(
        nullptr != pointElement,
        "No Point element found in XMLElement passed to CAnimationLoader::LoadFrame");
    
    CPoint2D<int> point;
    point.X() = pointElement->IntAttribute("X");
    point.Y() = pointElement->IntAttribute("Y");
    frame.SetImageOffset(point);
    
    m_spAnimation->AddFrame(frame);
}

//
// Load an animation sequence from a file stream
//
void CAnimationLoader::LoadSequence(tinyxml2::XMLElement * element)
{
    GameAssert(nullptr != element, "Null element passed to CAnimationLoader::LoadSequence");
    
    std::vector<unsigned int> sequence;
    
    tinyxml2::XMLElement * nextElement = element->FirstChildElement();
    while(nullptr != nextElement)
    {
        int value = 0;
        int error = nextElement->QueryIntText(&value);
        
        GameAssert(
            0 == error,
            "Failed to get integer value from sequence element in CAnimationLoader::LoadSequence");
        
        nextElement = nextElement->NextSiblingElement();
        sequence.push_back(value);
    }
    
    m_spAnimation->SetSequence(sequence);
}

//
// Load an animation from a file
//
std::shared_ptr<CAnimation> CAnimationLoader::Load(const std::string & animationFileName)
{
    using namespace tinyxml2;
    
    m_spAnimation = std::make_shared<CAnimation>();
    
    XMLDocument animDocument;
    animDocument.LoadFile(animationFileName.c_str());
    XMLElement * animElement = animDocument.RootElement();

    m_spAnimation->SetName(std::string(animElement->Attribute(NAME_TOKEN.c_str())));
    m_spAnimation->SetFrameRate(animElement->DoubleAttribute(FRAME_RATE_TOKEN.c_str()));

    XMLElement * nextElement = animElement->FirstChildElement();
    while(nullptr != nextElement)
    {
        m_animationLoadActions.at(nextElement->Name())(nextElement);
        nextElement = nextElement->NextSiblingElement();
    }

    return m_spAnimation;
}


