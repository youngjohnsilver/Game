//
//  keyboardinput.cpp
//  Game
//
//  Created by John Theiss on 7/20/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#include "keyboardinput.h"

// Standard dependencies
#include <algorithm>

// SDL dependencies
#include "SDL/SDL.h"

//
// Constructor
//
CKeyboardInput::CKeyboardInput()
{
    BuildKeyMap();
}

//
// Destructor
//
CKeyboardInput::~CKeyboardInput()
{
}

//
// Read only access to the keys that were pressed
//
const std::set<std::string> & CKeyboardInput::GetKeysPressed()const
{
    return m_keysPressed;
}

//
// Handle input events from SDL
//
void CKeyboardInput::HandleInput(const SDL_Event & event)
{
    // When a key goes down, add it to keysPressed
    if(event.type == SDL_KEYDOWN)
    {
        HandleKeyDown(event);
    }
    // When a key comes up remove it from keysPressed
    else if(event.type == SDL_KEYUP)
    {
        HandleKeyUp(event);
    }
}

//
// Respond to KEYUP events
//
void CKeyboardInput::HandleKeyUp(const SDL_Event & event)
{
    int keyType = event.key.keysym.sym;
    auto keyTypeIter = m_keyMap.find(keyType);
    if(keyTypeIter != m_keyMap.end())
    {
        auto pressedKeyIter = m_keysPressed.find(keyTypeIter->second);
        if(pressedKeyIter != m_keysPressed.end())
        {
            m_keysPressed.erase(pressedKeyIter);
        }
    }
}

//
// Respond to KEYDOWN events
//
void CKeyboardInput::HandleKeyDown(const SDL_Event & event)
{
    int keyType = event.key.keysym.sym;
    auto keyTypeIter = m_keyMap.find(keyType);
    if(keyTypeIter != m_keyMap.end())
    {
        m_keysPressed.insert(keyTypeIter->second);
    }
}

//
// Clear the keys that have been pressed
//
void CKeyboardInput::ClearInput()
{
    m_keysPressed.clear();
}

//
// Create mappings for the SDL KeyTypes
//
void CKeyboardInput::BuildKeyMap()
{
    // TODO Load these from a file
    m_keyMap =
    {
        {SDLK_UP, "UP"},
        {SDLK_DOWN, "DOWN"},
        {SDLK_LEFT, "LEFT"},
        {SDLK_RIGHT, "RIGHT"},

        {SDLK_w, "UP"},
        {SDLK_s, "DOWN"},
        {SDLK_a, "LEFT"},
        {SDLK_d, "RIGHT"}
    };
}
