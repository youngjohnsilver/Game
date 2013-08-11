//
//  characterview.cpp
//  Game
//
//  Created by John Theiss on 7/20/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#include "characterview.h"

// Project dependencies
#include "gameimage.h"
#include "ianimation.h"
#include "screenview.h"

using N_ScreenView::ApplySurface;
using N_ScreenView::ConvertToRect;

//
// Constructor
//
CCharacterView::CCharacterView(const SCharacterViewData & data) :
    m_data(data)
{
}

//
// Destructor
//
CCharacterView::~CCharacterView()
{
}

//
// View Interface
//
void CCharacterView::Draw(SDL_Surface * drawSurface, const CCamera & camera)const
{
    SDL_Rect clipRect = ConvertToRect(GetCurrentFrame());
    CPoint2D<int> screenPosition = camera.WorldToScreenTransform(GetPosition());
    for(auto layer : m_data.m_characterLayers)
    {
        ApplySurface(screenPosition, layer->GetSurface(), drawSurface, &clipRect);
    }
}

//
// Update animations
//
void CCharacterView::Update(const double timeSlice, const double frameRate)
{
    auto currentAnimation = m_data.m_animations.find(m_data.m_currentAnimationName);
    if(currentAnimation != m_data.m_animations.end())
    {
        currentAnimation->second->Update(timeSlice, frameRate);
    }
}

//
// Access image position
//
CPoint2D<int> CCharacterView::GetPosition()const
{
    return m_data.m_position;
}

int CCharacterView::GetZLevel()const
{
    return m_data.m_zLevel;
}

void CCharacterView::SetPosition(const CPoint2D<int> & position)
{
    m_data.m_position = position;
}

//
// Access image
//
std::vector<std::shared_ptr<CGameImage>> CCharacterView::GetLayers()const
{
    return m_data.m_characterLayers;
}

//
// Access current frame
//
CAnimationFrame CCharacterView::GetCurrentFrame()const
{
    CAnimationFrame frame;
    auto currentAnimation = m_data.m_animations.find(m_data.m_currentAnimationName);
    if(currentAnimation != m_data.m_animations.end())
    {
        frame = currentAnimation->second->GetCurrentFrame();
    }
    return frame;
}

//
// Change to a different animation
//
void CCharacterView::SetCurrentAnimation(const std::string & animationName)
{
    m_data.m_currentAnimationName = animationName;
}

//
// Change all animations
//
void CCharacterView::SetAnimations(const std::map<std::string, std::shared_ptr<IAnimation> > &animations)
{
    m_data.m_animations = animations;
}





