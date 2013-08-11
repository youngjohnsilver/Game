//
//  animation.cpp
//  Game
//
//  Created by John Theiss on 7/20/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#include "animation.h"

// Standard dependencies
#include <sstream>

// Project dependencies
#include "gameassert.h"

using N_GameAssert::GameAssert;

//
// Constructor
//
CAnimation::CAnimation() :
    m_frameRate(0.0),
    m_framesAccumulated(0.0),
    m_currentIndex(0)
{
}

CAnimation::CAnimation(
    const std::vector<CAnimationFrame> & frames,
    const std::vector<unsigned int> & sequence,
    const double frameRate) :
        m_frames(frames),
        m_sequence(sequence),
        m_frameRate(frameRate),
        m_framesAccumulated(0.0),
        m_currentIndex(0)
{
}

//
// Destructor
//
CAnimation::~CAnimation()
{
}

//
// Determine which frame is the current frame
//
CAnimationFrame CAnimation::GetCurrentFrame()const
{
    // std::vector::at will perform bounds checking
    CAnimationFrame frame;
    try
    {
        frame = m_frames.at(m_sequence.at(m_currentIndex));
    }
    catch(std::out_of_range & error)
    {
        std::stringstream errorMessage;
        errorMessage << error.what();
        errorMessage << " out of range. In CAnimation::GetCurrentFrame.\n";
        errorMessage << "Current Sequence Index: " << m_currentIndex << "\n";
        errorMessage << "Current Sequence Size: " << m_sequence.size() << "\n";
        errorMessage << "Sequence Elements:\n";
        for(auto element : m_sequence)
        {
            errorMessage << element << "\n";
        }
        errorMessage << "Number of Frames: " << m_frames.size() << std::endl;
        
        GameAssert(false, errorMessage.str());
    }
    return frame; //m_frames.at(m_sequence.at(m_currentIndex));
}

//
// Update the index of the animation
//
void CAnimation::Update(const double timeSlice, const double frameRate)
{
    m_frameRate = frameRate;
    
    // timeslice in seconds
    // frame rate in frames per second
    // seconds multiplied by frames per second = frame
    m_framesAccumulated += timeSlice * m_frameRate;
    
    while(m_framesAccumulated > 1.0)
    {
        IncrementCurrentIndex();
        m_framesAccumulated -= 1.0;
    }
}

//
// Increment the currentIndex, wrapping it around at the end of the sequence
//
void CAnimation::IncrementCurrentIndex()
{
    ++m_currentIndex;
    if(m_currentIndex >= m_sequence.size())
    {
        m_currentIndex = 0;
    }
}
