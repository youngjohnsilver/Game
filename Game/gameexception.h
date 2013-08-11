//
//  gameexception.h
//  Game
//
//  Created by John Theiss on 7/19/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#ifndef Game_gameexception_h
#define Game_gameexception_h

// Standard dependencies
#include <exception>
#include <string>

class CGameException : public std::exception
{
public:
    explicit CGameException(const std::string errorMessage);
    virtual ~CGameException();
    
    virtual const char * what() const noexcept;
    
private:
    std::string m_errorMessage;
};

#endif
