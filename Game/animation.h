//
//  animation.h
//  Game
//
//  Created by John Theiss on 7/20/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#ifndef Game_animation_h
#define Game_animation_h

// Standard dependencies
#include <string>
#include <vector>

// Project dependencies
#include "animationframe.h"
#include "ianimation.h"

class CAnimation : public IAnimation
{
public:
    CAnimation(
        const std::vector<CAnimationFrame> & frames,
        const std::vector<unsigned int> & sequence,
        const double frameRate);
    CAnimation();
    CAnimation(const CAnimation & animation) = default;
    CAnimation(CAnimation && animation) = default;
    CAnimation & operator=(const CAnimation & animation) = default;
    
    virtual ~CAnimation();
    
    // IAnimation interface
    virtual CAnimationFrame GetCurrentFrame()const override;
    virtual void Update(const double timeSlice, const double frameRate) override;
    
    std::string GetName()const { return m_name; }
    void AddFrame(const CAnimationFrame & frame) { m_frames.push_back(frame); }
    void SetSequence(const std::vector<unsigned int> & sequence) { m_sequence = sequence; }
    void SetFrameRate(const double frameRate) { m_frameRate = frameRate; }
    void SetName(const std::string & name) { m_name = name; }
    
private:
    void IncrementCurrentIndex();
    
private:
    std::string m_name;
    std::vector<CAnimationFrame> m_frames;
    std::vector<unsigned int> m_sequence;
    double m_frameRate;
    double m_framesAccumulated;
    unsigned int m_currentIndex;
};

#endif
