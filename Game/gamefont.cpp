//
//  gamefont.cpp
//  Game
//
//  Created by John Theiss on 7/19/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#include "gamefont.h"

// Standard dependencies
#include <exception>

// SDL dependencies
#include "SDL_ttf/SDL_ttf.h"

//
// Constructor - throws a runtime_error if the font file does not open
//
CGameFont::CGameFont(const std::string & trueTypeFontFileName, const unsigned int pointSize)
{
    m_sdlFont = TTF_OpenFont(trueTypeFontFileName.c_str(), pointSize);
    
    if(nullptr == m_sdlFont)
    {
        std::string errorMessage("Failed to load font: ");
        errorMessage += trueTypeFontFileName;
        throw(std::runtime_error(errorMessage));
    }
}

//
// Destructor
//
CGameFont::~CGameFont()
{
    TTF_CloseFont(m_sdlFont);
}

//
// Return the font * for use in other SDL objects
//
TTF_Font * CGameFont::GetFont()const
{
    return m_sdlFont;
}
