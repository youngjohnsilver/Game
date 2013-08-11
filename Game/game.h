//
//  game.h
//  Game
//
//  Created by John Theiss on 7/19/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#ifndef Game_game_h
#define Game_game_h

// Standard dependencies
#include <memory>

// Forward declarations
class CGameFont;
class CGameLevel;
class CGameTimer;
class CPlayerController;
class CKeyboardInput;

namespace N_ScreenView
{
class CScreenView;
}

//
// This is the game
//
class CGame
{
public:
    CGame();
    ~CGame();
    
    void Initialize();
    void Play();

private:
    // Game loop
    void HandleInput();
    void CalculateTimeSlice();
    
    // Framerate
    void SetFrameRateCap(double frameRateCap);
    double GetFrameRateCap()const;
    double GetTimeSlice()const;
    
    // Debug
    void DisplayFrameRate();
    void DisplayPlayerPosition();
    
    void Cleanup();
    
    void SaveCharacter(const std::string & fileName);

private:
    bool m_quit;
    std::unique_ptr<CGameFont> m_upFont;
    std::unique_ptr<CGameTimer> m_upFrameTimer;
    std::unique_ptr<N_ScreenView::CScreenView> m_upScreenView;
    std::unique_ptr<CPlayerController> m_upPlayerController;
    std::shared_ptr<CGameLevel> m_spLevel;
    std::shared_ptr<CKeyboardInput> m_spKeyboardInput;
    double m_inverseFrameRateCap;
    double m_timeSlice;
};

#endif
