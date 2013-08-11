//
//  gametimer.h
//  Game
//
//  Created by John Theiss on 7/20/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#ifndef Game_gametimer_h
#define Game_gametimer_h

class CGameTimer
{
public:
    CGameTimer();
    ~CGameTimer() = default;
    
    void Start();
    void Stop();
    void Pause();
    void Unpause();
    
    bool IsRunning()const;
    bool IsPaused()const;
    
    unsigned int GetTicks()const;

private:
    unsigned int m_startTicks;
    unsigned int m_pausedTicks;
    bool m_started;
    bool m_paused;
};

#endif
