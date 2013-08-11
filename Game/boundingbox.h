//
//  boundingbox.h
//  Game
//
//  Created by John Theiss on 7/21/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#ifndef Game_boundingbox_h
#define Game_boundingbox_h

// Project dependencies
#include "point2d.h"

struct SBoundingBox
{
    CPoint2D<int> m_position;
    int m_width;
    int m_height;
};

#endif
