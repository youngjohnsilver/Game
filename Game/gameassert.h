//
//  gameassert.h
//  Game
//
//  Created by John Theiss on 7/20/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#ifndef Game_gameassert_h
#define Game_gameassert_h

// Standard dependencies
#include <exception>
#include <string>

namespace N_GameAssert
{

inline void GameAssert(bool condition, const std::string & message)
{
    if(!condition)
    {
        throw(std::runtime_error(message));
    }
}

}

#endif
