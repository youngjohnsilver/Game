//
//  gametimer.cpp
//  Game
//
//  Created by John Theiss on 7/20/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#include "gametimer.h"

// SDL dependencies
#include "SDL/SDL.h"

//
// Constructor
//
CGameTimer::CGameTimer() :
    m_startTicks(0),
    m_pausedTicks(0),
    m_started(false),
    m_paused(false)
{
}

//
// Start the timer
//
void CGameTimer::Start()
{
    m_started = true;
    m_paused = false;
    m_startTicks = SDL_GetTicks();
}

//
// Stop the timer
//
void CGameTimer::Stop()
{
    m_started = false;
    m_paused = false;
}

//
// Pause the timer
//
void CGameTimer::Pause()
{
    // the timer has to be running for pause to have an effect
    if(m_started && !m_paused)
    {
        m_pausedTicks = SDL_GetTicks() - m_startTicks;
        m_paused = true;
    }
}

//
// Unpause the timer
//
void CGameTimer::Unpause()
{
    if(m_paused)
    {
        m_startTicks = SDL_GetTicks() - m_pausedTicks;
        m_pausedTicks = 0;
        m_paused = false;
    }
}

//
// Get the number of ticks since the timer was last started
// returns 0 if the timer is stopped
// returns the time at which the timer was paused if the timer is paused
//
unsigned int CGameTimer::GetTicks()const
{
    unsigned int ticks = 0;
    if(m_started)
    {
        // if the timer was paused
        // return only how many ticks passed when it was first paused
        if(m_paused)
        {
            ticks = m_pausedTicks;
        }
        else
        {
            ticks = SDL_GetTicks() - m_startTicks;
        }
    }
    return ticks;
}

//
// Is the timer running
//
bool CGameTimer::IsRunning()const
{
    return m_started;
}
bool CGameTimer::IsPaused()const
{
    return m_paused;
}
