//
//  camera.cpp
//  Game
//
//  Created by John Theiss on 7/21/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#include "camera.h"

// Project dependencies
#include "characterview.h"
#include "gamelevel.h"

//
// Constructor
//
CCamera::CCamera(
    const int screenWidth,
    const int screenHeight,
    const int worldWidth,
    const int worldHeight) :
        m_position{1600, 1600},
        m_screenLookAt{screenWidth / 2, screenHeight / 2}
{
    m_cameraBounds.m_position = {250, 200};
    m_cameraBounds.m_width = screenWidth - m_cameraBounds.m_position.X();
    m_cameraBounds.m_height = screenHeight - m_cameraBounds.m_position.Y();
    
    m_worldBounds.m_position = {0,0};
    m_worldBounds.m_width = worldWidth;
    m_worldBounds.m_height = worldHeight;
}

//
// Transform a point from world coordinates to screen coordinates
//
CPoint2D<int> CCamera::WorldToScreenTransform(
    const CPoint2D<int> & worldCoordinates)const
{
    CPoint2D<int> screenCoordinates;
    
    screenCoordinates.X() = worldCoordinates.X() - m_position.X() + m_screenLookAt.X();
    screenCoordinates.Y() = worldCoordinates.Y() - m_position.Y() + m_screenLookAt.Y();
    
    return screenCoordinates;
}

//
// Focus on a specific character by moving the camera to the character's
// position to center it on screen.
// This character also becomes the object which can push the camera around to other positions
// when the character collides with the camera's bounding box
//
void CCamera::FocusOnCharacter(std::weak_ptr<const CCharacterView> character)
{
    m_characterInFocus = character;
    ZoomToFocusedCharacter();
}

//
// Set position to the focused character's position and clip to world
//
void CCamera::ZoomToFocusedCharacter()
{
    std::shared_ptr<const CCharacterView> spCharacter = m_characterInFocus.lock();
    if(nullptr != spCharacter)
    {
        m_position = spCharacter->GetPosition();
        CapPositionToWorld();
    }
}

//
// Update the camera's world bounds to match the bounds of the level
//
void CCamera::UpdateWorldBounds(std::weak_ptr<const CGameLevel> level)
{
    m_worldBounds.m_height = level.lock()->GetHeight();
    m_worldBounds.m_width = level.lock()->GetWidth();
}

//
// Cap the camera's position to prevent it from viewing negative world values
//
void CCamera::CapPositionToWorld()
{
    if(m_position.X() - m_screenLookAt.X() < m_worldBounds.m_position.X())
    {
        m_position.X() = m_worldBounds.m_position.X() + m_screenLookAt.X();
    }
    if(m_position.Y() - m_screenLookAt.Y() < m_worldBounds.m_position.Y())
    {
        m_position.Y() = m_worldBounds.m_position.Y() + m_screenLookAt.Y();
    }
    if(m_position.X() + m_screenLookAt.X() > m_worldBounds.m_width)
    {
        m_position.X() = m_worldBounds.m_width - m_screenLookAt.X();
    }
    if(m_position.Y() + m_screenLookAt.Y() > m_worldBounds.m_height)
    {
        m_position.Y() = m_worldBounds.m_width - m_screenLookAt.Y();
    }
}

//
// Update camera position based on the character in focus
//
void CCamera::Update()
{
    std::shared_ptr<const CCharacterView> spCharacter = m_characterInFocus.lock();
    if(nullptr != spCharacter)
    {
        CPoint2D<int> characterScreenCoordinates = WorldToScreenTransform(spCharacter->GetPosition());
        
        // push the camera to keep the character within the camera bounding box
        
        // Push left
        int xDiff = m_cameraBounds.m_position.X() - characterScreenCoordinates.X();
        if(xDiff > 0)
        {
            m_position.X() -= xDiff;
        }
        
        // Push right
        int wDiff = characterScreenCoordinates.X() - m_cameraBounds.m_width;
        if(wDiff > 0)
        {
            m_position.X() += wDiff;
        }
        
        // Push up
        int yDiff = m_cameraBounds.m_position.Y() - characterScreenCoordinates.Y();
        if(yDiff > 0)
        {
            m_position.Y() -= yDiff;
        }
        
        // Push down
        int hDiff = characterScreenCoordinates.Y() - m_cameraBounds.m_height;
        if(hDiff > 0)
        {
            m_position.Y() += hDiff;
        }
        CapPositionToWorld();
    }
}

//
// Check if a bounding box is at least partially on screen
//
bool CCamera::IsOnScreen(const SBoundingBox & box)const
{
    CPoint2D<int> screenPoint = WorldToScreenTransform(box.m_position);
    CPoint2D<int> cameraPoint = WorldToScreenTransform(m_position);
    
    int screenWidth = m_screenLookAt.X() * 2;
    int screenHeight = m_screenLookAt.Y() * 2;
    
    int dX = abs(screenPoint.X() - cameraPoint.X());
    int dY = abs(screenPoint.Y() - cameraPoint.Y());
    int totalWidth = box.m_width + screenWidth;
    int totalHeight = box.m_height + screenHeight;
    
    bool onScreen = false;
    if(dX * 2 <= totalWidth && dY * 2 <= totalHeight)
    {
        onScreen = true;
    }
    return onScreen;
}







