//
//  gamefont.h
//  Game
//
//  Created by John Theiss on 7/19/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#ifndef Game_gamefont_h
#define Game_gamefont_h

// Standard dependencies
#include <string>

// SDL dependencies
#include "SDL_ttf/SDL_ttf.h"

//
// This is a wrapper around SDL's TTF_Font
// RAII is used to open the font upon construction
// and close the font upon destruction
//
class CGameFont
{
public:
    explicit CGameFont(const std::string & trueTypeFontFileName, const unsigned int pointSize = 28);
    ~CGameFont();
    
    TTF_Font * GetFont()const;
    
private:
    // No copy, no move
    CGameFont(const CGameFont &) = delete;
    CGameFont(const CGameFont &&) = delete;
    CGameFont & operator=(const CGameFont &) = delete;
    
private:
    TTF_Font * m_sdlFont;
};

#endif
