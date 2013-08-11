//
//  keyboardinput.h
//  Game
//
//  Created by John Theiss on 7/20/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#ifndef Game_keyboardinput_h
#define Game_keyboardinput_h

// Standard dependencies
#include <map>
#include <set>
#include <string>

// Project dependencies
#include "ikeyboardinput.h"

// Forward declarations
union SDL_Event;

class CKeyboardInput : public IKeyboardInput
{
public:
    CKeyboardInput();
    virtual ~CKeyboardInput();
    
    // IKeyboardInput interface
    const std::set<std::string> & GetKeysPressed()const;
    
    void HandleInput(const SDL_Event & event);
    void ClearInput();
    
private:
    void BuildKeyMap();
    void HandleKeyUp(const SDL_Event & event);
    void HandleKeyDown(const SDL_Event & event);
    
private:
    std::map<int, std::string> m_keyMap;
    std::set<std::string> m_keysPressed;
};

#endif
