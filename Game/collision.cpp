//
//  collision.cpp
//  Game
//
//  Created by John Theiss on 7/30/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#include "collision.h"

// Standard dependencies
#include <stdlib.h>

// Project dependencies
#include "boundingbox.h"

namespace N_Collision
{

bool Collides(const SBoundingBox & box1, const SBoundingBox & box2)
{
    bool collides = false;
    int dX = abs(box1.m_position.X() - box2.m_position.X());
    int dY = abs(box1.m_position.Y() - box2.m_position.Y());
    int totalWidth = box1.m_width + box2.m_width;
    int totalHeight = box1.m_height + box2.m_height;
    
    if(dX*2 <= totalWidth && dY*2 <= totalHeight)
    {
        collides = true;
    }
    
    return collides;
}

}
