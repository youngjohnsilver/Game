//
//  commonloader.cpp
//  Game
//
//  Created by John Theiss on 7/21/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#include "commonloader.h"

// Project dependencies
#include "animation.h"
#include "animationloader.h"
#include "characterloader.h"
#include "levelloader.h"
#include "characterview.h"
#include "gameassert.h"
#include "gamelevel.h"

using N_GameAssert::GameAssert;

namespace
{

const std::string X_TOKEN("X");
const std::string Y_TOKEN("Y");

}

namespace N_CommonLoader
{

//
// Load an animation from a file
//
std::shared_ptr<CAnimation> LoadAnimation(const std::string & fileName)
{
    CAnimationLoader loader;
    return loader.Load(fileName);
}

//
// Load a character from a file
//
std::shared_ptr<CCharacterView> LoadCharacter(const std::string & fileName)
{
    CCharacterLoader loader;
    return loader.Load(fileName);
}

//
// Load a character from a file
//
std::shared_ptr<CGameLevel> LoadLevel(const std::string & fileName)
{
    CLevelLoader loader;
    return loader.Load(fileName);
}

}
