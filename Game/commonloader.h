//
//  commonloader.h
//  Game
//
//  Created by John Theiss on 7/21/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#ifndef Game_commonloader_h
#define Game_commonloader_h

// Standard dependencies
#include <memory>
#include <string>

// Forward declarations
class CAnimation;
class CCharacterView;
class CGameLevel;

namespace N_CommonLoader
{

std::shared_ptr<CAnimation> LoadAnimation(const std::string & string);
std::shared_ptr<CCharacterView> LoadCharacter(const std::string & characterFileName);
std::shared_ptr<CGameLevel> LoadLevel(const std::string & levelFileName);

}

#endif
