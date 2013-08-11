//
//  gameimage.cpp
//  Game
//
//  Created by John Theiss on 7/20/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#include "gameimage.h"

// Standard dependencies
#include <algorithm>

// SDL dependencies
#include "SDL/SDL.h"
#include "SDL_image/SDL_image.h"

// Project dependencies
#include "gameassert.h"

using N_GameAssert::GameAssert;

//
// Constructor
//
CGameImage::CGameImage() :
    m_sdlImage(nullptr)
{
}

//
// Destructor
//
CGameImage::~CGameImage()
{
    // NOTE:
    // It is safe to free a nullptr
    // according to SDL documentation
    SDL_FreeSurface(m_sdlImage);
}

//
// Load an image and format it to the appropriate display format
// will throw a runtime_error if the image doesn't load
// or if the image doesn't format correctly
//
void CGameImage::LoadImage(const std::string & imageFileName)
{
    SDL_Surface * loadedImage = nullptr;
    
    loadedImage = IMG_Load(imageFileName.c_str());
    if(nullptr == loadedImage)
    {
        std::string errorMessage("Failed to load image: ");
        errorMessage += imageFileName;
        GameAssert(false, errorMessage);
    }
    
    // Convert the loaded image to the current display format
    SDL_Surface * optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
    
    // the loaded image is no longer needed and must be freed
    // free the loaded image surface before potentially throwing
    // an exception for an SDL_DisplayFormat error
    SDL_FreeSurface(loadedImage);
    
    if(nullptr == optimizedImage)
    {
        std::string errorMessage("Failed to format the image: ");
        errorMessage += imageFileName;
        errorMessage += std::string(" to the current display format");
        GameAssert(false, errorMessage);
    }
    
    // if everything worked, store the optimized image as the member
    // and free the old image 
    std::swap(m_sdlImage, optimizedImage);
    SDL_FreeSurface(optimizedImage);
}

//
// Allow access to the sdl surface
//
SDL_Surface * CGameImage::GetSurface()const
{
    return m_sdlImage;
}

void CGameImage::SetSurface(SDL_Surface * newSurface)
{
    std::swap(m_sdlImage, newSurface);
    SDL_FreeSurface(newSurface);
}









