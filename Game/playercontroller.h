//
//  playercontroller.h
//  Game
//
//  Created by John Theiss on 7/20/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#ifndef Game_playercontroller_h
#define Game_playercontroller_h

// Standard dependencies
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

// Project dependencies
#include "boundingbox.h"
#include "point2d.h"

// Forward declarations
class CCharacterView;
class IKeyboardInput;

class CPlayerController
{
public:
    CPlayerController() = default;
    ~CPlayerController() = default;
    
    void LoadPlayer();
    
    void HandleInput(const std::weak_ptr<const IKeyboardInput> wpKeyboardInput);
    void Update(
        const double timeSlice,
        const std::vector<std::shared_ptr<SBoundingBox>> collisionData);
    
    std::weak_ptr<const CCharacterView> GetCharacterView()const;
    SBoundingBox GetCollisionBounds()const { return m_bounds; }
    
private:
    void BuildKeyActionMap();
    void SetBounds();

    double CalculateFrameRate()const;
        
    // Player actions
    void MoveUp();
    void MoveLeft();
    void MoveDown();
    void MoveRight();
    void StopMoving();
    
private:
    std::shared_ptr<CCharacterView> m_spPlayerView;
    
    double m_currentTimeSlice;
    
    // walk speed is measured in pixels per second
    double m_walkSpeed;
    
    // walk pace is measured in frames per pixel (walk animation frames)
    double m_walkPace;
    
    // velocity is a directional vector with magnitude equal to walk speed
    CPoint2D<int> m_velocity;
    
    struct SBoundingBox m_bounds;
    std::map<std::string, std::function<void ()>> m_keyActionMap;
    std::string m_orientation;
};

#endif
