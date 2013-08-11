//
//  screenview.cpp
//  Game
//
//  Created by John Theiss on 7/18/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#include "screenview.h"

// Standard dependencies
#include <exception>

// SDL dependencies
#include "SDL/SDL.h"
#include "SDL_image/SDL_image.h"
#include "SDL_ttf/SDL_ttf.h"
#include "SDL_gfxPrimitives.h"

// Project dependencies
#include "animationframe.h"
#include "camera.h"
#include "characterview.h"
#include "gameassert.h"
#include "gameimage.h"
#include "gamelevel.h"
#include "gametile.h"
#include "iview.h"
#include "screenattributes.h"

using N_GameAssert::GameAssert;

namespace N_ScreenView
{

SDL_Rect ConvertToRect(const CAnimationFrame & frame)
{
    CPoint2D<int> offset = frame.GetImageOffset();
    SDL_Rect rect;
    rect.x = offset.X();
    rect.y = offset.Y();
    rect.w = frame.GetWidth();
    rect.h = frame.GetHeight();
    
    return rect;
}

SDL_Rect ConvertToRect(const SBoundingBox & box)
{
    CPoint2D<int> offset = box.m_position;
    SDL_Rect rect;
    rect.x = offset.X();
    rect.y = offset.Y();
    rect.w = box.m_width;
    rect.h = box.m_height;
    
    return rect;
}
    
//
// Blits a source to a destination with the given xy offset.
//
void ApplySurface(
    const CPoint2D<int> & offset,
    SDL_Surface * source,
    SDL_Surface * destination,
    SDL_Rect * clipRect)
{
    SDL_Rect offsetRect;
    offsetRect.x = offset.X();
    offsetRect.y = offset.Y();
        
    SDL_BlitSurface(source, clipRect, destination, &offsetRect);
}
    
//
// Constructor
//
CScreenView::CScreenView() :
    m_screen(nullptr)
{
}

//
// Destructor
//
CScreenView::~CScreenView()
{
    Cleanup();
}

//
// Initialize all members
//
void CScreenView::Initialize()
{
    SScreenAttributes screenData = {1024, 768, 32};
    
    // Setup screen
    m_screen = SDL_SetVideoMode(
        screenData.m_width,
        screenData.m_height,
        screenData.m_bitsPerPixel,
        SDL_SWSURFACE);
    
    GameAssert(nullptr != m_screen, std::string("Screen failed to initialize"));
    
    SDL_WM_SetCaption("Game", nullptr);
    
    m_upMessage.reset(new CGameImage());
    int worldWidth = 0;
    int worldHeight = 0;
    
    m_upCamera.reset(new CCamera(screenData.m_width, screenData.m_height, worldWidth, worldHeight));
}

//
// Load in all of the views from a level
//
void CScreenView::LoadLevel(
    const std::weak_ptr<const CGameLevel> wpLevel,
    const std::weak_ptr<const CCharacterView> wpCharacter)
{
    m_upCamera->UpdateWorldBounds(wpLevel);
    m_upCamera->FocusOnCharacter(wpCharacter);
    
    std::vector<std::shared_ptr<const IView>> views;
    auto layers = wpLevel.lock()->GetLayers();
    int zLevel = 0;
    for(auto layer : layers)
    {
        for(auto tile : layer)
        {
            views.push_back(std::static_pointer_cast<const IView>(tile));
        }
        if(zLevel == wpCharacter.lock()->GetZLevel())
        {
            views.push_back(std::static_pointer_cast<const IView>(wpCharacter.lock()));
        }
        ++zLevel;
    }
    
    m_loadedViews = views;
}
//
// Destroy all objects
//
void CScreenView::Cleanup()
{
    m_upMessage.reset();
}

//
// Draw the given object
//
void CScreenView::DrawSurface(
    const CPoint2D<int> & position,
    SDL_Surface * source,
    SDL_Rect * clipRect)
{
    CPoint2D<int> screenOffset = m_upCamera->WorldToScreenTransform(position);
    ApplySurface(screenOffset, source, m_screen, clipRect);
}

//
// Cover up the screen with the background
//
void CScreenView::ClearScreen()
{
    SDL_FillRect(m_screen, nullptr, SDL_MapRGBA(m_screen->format, 0x10, 0xDC, 0x73, 0xFF));
}

//
// Move the camera to the character
//
void CScreenView::FocusCameraOnCharacter(const std::weak_ptr<const CCharacterView> wpCharacter)
{
    m_upCamera->FocusOnCharacter(wpCharacter);
}

//
// Draw all of the screens views
//
void CScreenView::DrawViews()
{
    for(const auto & view : m_loadedViews)
    {
        view->Draw(m_screen, *m_upCamera);
    }
}

//
// Draw the collision boxes for a level's collision data
//
void CScreenView::DrawCollisionData(const std::vector<std::shared_ptr<SBoundingBox> > collisionData)
{
    for(const auto & spBox : collisionData)
    {
        DrawBox(*spBox);
    }
}

//
// Draw a bounding box
//
void CScreenView::DrawBox(const SBoundingBox & box)
{
    CPoint2D<int> screenOffset = m_upCamera->WorldToScreenTransform(box.m_position);

    int halfWidth = box.m_width / 2;
    int halfHeight = box.m_height / 2;
    short x = screenOffset.X() - halfWidth;
    short y = screenOffset.Y() - halfHeight;
    short w = box.m_width + x;
    short h = box.m_height + y;
    rectangleRGBA(m_screen, x, y, w, h, 255, 255, 0, 255);
}

//
// Write a message to the screen
//
void CScreenView::WriteMessage(
    const std::string messageText,
    const CPoint2D<int> & position,
    TTF_Font * font,
    const SDL_Color & textColor)
{
    m_upMessage->SetSurface(TTF_RenderText_Solid(font, messageText.c_str(), textColor));
    GameAssert(nullptr != m_upMessage->GetSurface(), std::string("Failed to render text"));
    
    ApplySurface(position, m_upMessage->GetSurface(), m_screen);
}

//
// Display
//
void CScreenView::Display()
{
    // update camera
    m_upCamera->Update();
    
    // update screen
    int result = SDL_Flip(m_screen);
    GameAssert(-1 != result, std::string("Screen failed to draw"));
}

}
















