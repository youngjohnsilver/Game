//
//  gameexception.cpp
//  Game
//
//  Created by John Theiss on 7/19/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#include "gameexception.h"

//
// Constructor
//
CGameException::CGameException(const std::string errorMessage) :
    m_errorMessage(errorMessage)
{
}

//
// Destructor
//
CGameException::~CGameException()
{
}

//
// what
//
const char * CGameException::what()const noexcept
{
    // This seems inappropriate
    std::string whatString(std::exception::what());
    whatString += m_errorMessage;
    
    return whatString.c_str();
}
