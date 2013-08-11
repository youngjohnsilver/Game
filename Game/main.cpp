//
//  main.cpp
//  Game
//
//  Created by John Theiss on 7/17/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

// Standard dependencies
#include <exception>
#include <iostream>

// SDL dependencies
#include "SDL/SDL.h"


// Project dependencies
#include "game.h"

//
// Main
//
int main( int argc, char* args[] )
{
    try
    {
        CGame game;
        game.Initialize();
        game.Play();
    }
    catch(std::out_of_range & error)
    {
        std::cerr << error.what();
        std::cerr << " out of range" << std::endl;
    }
    catch(std::exception & error)
    {
        std::cerr << error.what() << std::endl;
    }
    
    return 0;
}

