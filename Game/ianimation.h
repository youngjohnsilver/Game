//
//  ianimation.h
//  Game
//
//  Created by John Theiss on 7/20/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#ifndef Game_ianimation_h
#define Game_ianimation_h

// Project Dependencies
#include "animationframe.h"

class IAnimation
{
public:
    IAnimation() {}
    virtual ~IAnimation() {}
    
    virtual CAnimationFrame GetCurrentFrame()const = 0;
    virtual void Update(const double timeSlice, const double frameRate) = 0;
};

#endif
