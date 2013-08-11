//
//  ikeyboardinput.h
//  Game
//
//  Created by John Theiss on 7/20/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#ifndef Game_ikeyboardinput_h
#define Game_ikeyboardinput_h

// Standard dependencies
#include <set>
#include <string>

class IKeyboardInput
{
public:
    IKeyboardInput() {}
    virtual ~IKeyboardInput() {}
    
    virtual const std::set<std::string> & GetKeysPressed()const = 0;
};

#endif
