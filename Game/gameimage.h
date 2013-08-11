//
//  gameimage.h
//  Game
//
//  Created by John Theiss on 7/20/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#ifndef Game_gameimage_h
#define Game_gameimage_h

// Standard dependencies
#include <string>

// Forward declarations
struct SDL_Surface;

class CGameImage
{
public:
    CGameImage();
    ~CGameImage();
    
    void LoadImage(const std::string & imageFileName);
    SDL_Surface * GetSurface()const;
    void SetSurface(SDL_Surface * newSurface);
    
private:
    // No copy, no move
    CGameImage(const CGameImage &) = delete;
    CGameImage(const CGameImage &&) = delete;
    CGameImage & operator=(const CGameImage &) = delete;
    
private:
    SDL_Surface * m_sdlImage;
};

#endif
