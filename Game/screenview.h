//
//  screenview.h
//  Game
//
//  Created by John Theiss on 7/18/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#ifndef Game_screenview_h
#define Game_screenview_h

// Standard dependencies
#include <string>
#include <vector>

// SDL dependencies
#include "SDL_ttf/SDL_ttf.h"

// Project dependencies
#include "point2d.h"

// Forward declarations
class CAnimationFrame;
class CCamera;
class CCharacterView;
class CGameImage;
class CGameLevel;
class IView;
struct SBoundingBox;
struct SDL_Color;
struct SDL_Rect;
struct SDL_Surface;

namespace N_ScreenView
{

// Free functions
SDL_Surface * LoadImage(const std::string fileName);
void ApplySurface(
    const CPoint2D<int> & offset,
    SDL_Surface * source,
    SDL_Surface * destination,
    SDL_Rect * clipRect = nullptr);
    
SDL_Rect ConvertToRect(const CAnimationFrame & frame);
SDL_Rect ConvertToRect(const SBoundingBox & box);

class CScreenView
{
public:
    CScreenView();
    ~CScreenView();
    
    void Initialize();
    void Cleanup();
    void Display();
    void ClearScreen();
    void LoadLevel(
        const std::weak_ptr<const CGameLevel> wpLevel,
        const std::weak_ptr<const CCharacterView> wpCharacter);
    
    void WriteMessage(
        const std::string messageText,
        const CPoint2D<int> & position,
        TTF_Font * font,
        const SDL_Color & textColor);
    
    void FocusCameraOnCharacter(const std::weak_ptr<const CCharacterView> wpCharacter);
    void DrawViews();
    void DrawCollisionData(const std::vector<std::shared_ptr<SBoundingBox>> collisionData);
    void DrawBox(const SBoundingBox & box);
    
private:    
    void DrawSurface(
        const CPoint2D<int> & position,
        SDL_Surface * source,
        SDL_Rect * clipRect = nullptr);
    
private:
    SDL_Surface * m_screen;
    std::unique_ptr<CCamera> m_upCamera;
    std::unique_ptr<CGameImage> m_upMessage;
    std::unique_ptr<CGameImage> m_upBackground;
    std::vector<std::shared_ptr<const IView>> m_loadedViews;
};
    
}

#endif
