//
//  animationframe.h
//  Game
//
//  Created by John Theiss on 7/20/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#ifndef Game_animationframe_h
#define Game_animationframe_h

// Project dependencies
#include "point2d.h"

class CAnimationFrame
{
public:
    CAnimationFrame() = default;
    CAnimationFrame(
        const CPoint2D<int> & imageOffset,
        const unsigned int width,
        const unsigned int height);
    
    ~CAnimationFrame() = default;
    
    CPoint2D<int> GetImageOffset()const;
    unsigned int GetWidth()const;
    unsigned int GetHeight()const;
    
    void SetImageOffset(const CPoint2D<int> & imageOffset);
    void SetWidth(const unsigned int width);
    void SetHeight(const unsigned int height);
    
private:
    CPoint2D<int> m_imageOffset;
    unsigned int m_width;
    unsigned int m_height;
};

#endif
