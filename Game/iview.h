//
//  iview.h
//  Game
//
//  Created by John Theiss on 7/27/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#ifndef Game_iview_h
#define Game_iview_h

// SDL dependencies
#include "SDL/SDL.h"

// Project dependencies
#include "camera.h"

class IView
{
public:
    IView() = default;
    virtual ~IView() = default;
    
    virtual void Draw(SDL_Surface * drawSurface, const CCamera & camera)const = 0;
};

#endif
