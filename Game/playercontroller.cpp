//
//  playercontroller.cpp
//  Game
//
//  Created by John Theiss on 7/20/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#include "playercontroller.h"

// Project dependencies
#include "animationframe.h"
#include "collision.h"
#include "commonloader.h"
#include "characterview.h"
#include "gameassert.h"
#include "gamelevel.h"
#include "ikeyboardinput.h"

using N_GameAssert::GameAssert;

namespace
{
const std::string UP("Up");
const std::string DOWN("Down");
const std::string LEFT("Left");
const std::string RIGHT("Right");
}

//
// Load the player from the player file
//
void CPlayerController::LoadPlayer()
{
    m_spPlayerView = N_CommonLoader::LoadCharacter("./CharacterData/Erin.xml");
    GameAssert(nullptr != m_spPlayerView, std::string("Player failed to load"));
    BuildKeyActionMap();
    m_orientation = DOWN;
    std::string animationName("Stand");
    m_spPlayerView->SetCurrentAnimation(animationName + m_orientation);
    m_walkSpeed = 150.0;
    m_currentTimeSlice = 0.0;
    m_walkPace = 0.04;
    
    SetBounds();
}

//
// Set the player's bounding box data
//
void CPlayerController::SetBounds()
{
    const int SHADOW_HEIGHT = 10;
    const int SHADOW_OFFSET = 42;
    CPoint2D<int> viewPosition = m_spPlayerView->GetPosition();
    int viewWidth = m_spPlayerView->GetCurrentFrame().GetWidth();
    m_bounds.m_position.X() = viewPosition.X() + viewWidth / 2;
    m_bounds.m_position.Y() = viewPosition.Y() + SHADOW_OFFSET;
    m_bounds.m_width = viewWidth;
    m_bounds.m_height = SHADOW_HEIGHT;
}

//
// Respond to input
//
void CPlayerController::HandleInput(const std::weak_ptr<const IKeyboardInput> wpKeyboardInput)
{
    const std::set<std::string> & keysPressed = wpKeyboardInput.lock()->GetKeysPressed();
    for(auto key : keysPressed)
    {
        auto actionIter = m_keyActionMap.find(key);
        if(actionIter != m_keyActionMap.end())
        {
            actionIter->second();
        }
    }
    if(keysPressed.empty())
    {
        StopMoving();
    }
}

//
// Calculate the framerate of the walk animation based on speed and pace
//
double CPlayerController::CalculateFrameRate()const
{
    // frame rate in frames/second (f/s)
    // pace in frames/pixel (f/p)
    // speed in pixels/second (p/s)
    // f/s = f/p * p/s
    return m_walkPace * m_walkSpeed;
}

//
// Update the player's position based on velocity
//
void CPlayerController::Update(
    const double timeSlice,
    const std::vector<std::shared_ptr<SBoundingBox>> collisionData)
{
    m_currentTimeSlice = timeSlice;
        
    // Update animations
    m_spPlayerView->Update(timeSlice, CalculateFrameRate());
    
    // Create a temporary box with the player's updated position
    // to use for collision detection
    SBoundingBox collisionBox = m_bounds;
    collisionBox.m_position.X() +=  m_velocity.X();
    collisionBox.m_position.Y() +=  m_velocity.Y();

    bool collides = false;
    for(auto spBox : collisionData)
    {
        if(N_Collision::Collides(collisionBox, *spBox))
        {
            collides = true;
            break;
        }
    }
    if(!collides)
    {
        // if there was no collision commit the update
        // to the player's position
        m_bounds = collisionBox;
        
        CPoint2D<int> playerPosition = m_spPlayerView->GetPosition();
        playerPosition.X() += m_velocity.X();
        playerPosition.Y() += m_velocity.Y();
        m_spPlayerView->SetPosition(playerPosition);
    }
}

//
// Offer read only access to the character view
//
std::weak_ptr<const CCharacterView> CPlayerController::GetCharacterView()const
{
    return m_spPlayerView;
}

//
// Construct the key-action map which maps the player actions to keyboard keys
//
void CPlayerController::BuildKeyActionMap()
{
    // TODO move keyboard keys to a definitions file
    m_keyActionMap =
    {
        {"UP", std::bind(&CPlayerController::MoveUp, this)},
        {"DOWN", std::bind(&CPlayerController::MoveDown, this)},
        {"LEFT", std::bind(&CPlayerController::MoveLeft, this)},
        {"RIGHT", std::bind(&CPlayerController::MoveRight, this)}
    };
}

//
// Move the player in the cardinal directions
//
void CPlayerController::MoveUp()
{
    int magnitude = static_cast<int>(m_walkSpeed * m_currentTimeSlice + 0.5);
    m_velocity = {0, -magnitude};
    
    m_orientation = UP;
    std::string animationName("Walk");
    m_spPlayerView->SetCurrentAnimation(animationName + m_orientation);
}

void CPlayerController::MoveDown()
{
    int magnitude = static_cast<int>(m_walkSpeed * m_currentTimeSlice + 0.5);
    m_velocity = {0, magnitude};
    
    m_orientation = DOWN;
    std::string animationName("Walk");
    m_spPlayerView->SetCurrentAnimation(animationName + m_orientation);
}

void CPlayerController::MoveLeft()
{
    int magnitude = static_cast<int>(m_walkSpeed * m_currentTimeSlice + 0.5);
    m_velocity = {-magnitude, 0};
    
    m_orientation = LEFT;
    std::string animationName("Walk");
    m_spPlayerView->SetCurrentAnimation(animationName + m_orientation);
}

void CPlayerController::MoveRight()
{
    int magnitude = static_cast<int>(m_walkSpeed * m_currentTimeSlice + 0.5);
    m_velocity = {magnitude, 0};
    
    m_orientation = RIGHT;
    std::string animationName("Walk");
    m_spPlayerView->SetCurrentAnimation(animationName + m_orientation);
}

void CPlayerController::StopMoving()
{
    m_velocity = {0, 0};
    
    std::string animationName("Stand");
    m_spPlayerView->SetCurrentAnimation(animationName + m_orientation);
}