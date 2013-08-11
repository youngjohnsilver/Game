//
//  animationframe.cpp
//  Game
//
//  Created by John Theiss on 7/20/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#include "animationframe.h"

//
// Constructor
//
CAnimationFrame::CAnimationFrame(
    const CPoint2D<int> & imageOffset,
    unsigned int width,
    unsigned int height) :
        m_imageOffset(imageOffset),
        m_width(width),
        m_height(height)
{
}

//
// Accessors
//
CPoint2D<int> CAnimationFrame::GetImageOffset()const
{
    return m_imageOffset;
}

unsigned int CAnimationFrame::GetWidth()const
{
    return m_width;
}

unsigned int CAnimationFrame::GetHeight()const
{
    return m_height;
}

void CAnimationFrame::SetImageOffset(const CPoint2D<int> & imageOffset)
{
    m_imageOffset = imageOffset;
}

void CAnimationFrame::SetWidth(const unsigned int width)
{
    m_width = width;
}

void CAnimationFrame::SetHeight(const unsigned int height)
{
    m_height = height;
}
