//
//  camera.h
//  Game
//
//  Created by John Theiss on 7/21/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#ifndef Game_camera_h
#define Game_camera_h

// Standard dependencies
#include <memory>

// Project dependencies
#include "boundingbox.h"
#include "point2d.h"

// Forward declarations
class CCharacterView;
class CGameLevel;

class CCamera
{
public:
    CCamera(const int screenWidth, const int screenHeight, const int worldWidth, const int worldHeight);
    ~CCamera() = default;

    CPoint2D<int> WorldToScreenTransform(
        const CPoint2D<int> & worldCoordinates)const;
    
    bool IsOnScreen(const SBoundingBox & box)const;
    
    void FocusOnCharacter(std::weak_ptr<const CCharacterView> character);
    void UpdateWorldBounds(std::weak_ptr<const CGameLevel> level);
    void Update();
    
private:
    void ZoomToFocusedCharacter();
    void CapPositionToWorld();

private:
    CPoint2D<int> m_position;
    CPoint2D<int> m_screenLookAt;
    
    // bounds for collision detection
    SBoundingBox m_cameraBounds;
    SBoundingBox m_worldBounds;
    
    std::weak_ptr<const CCharacterView> m_characterInFocus;
};

#endif
