//
//  game.cpp
//  Game
//
//  Created by John Theiss on 7/19/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#include "game.h"

// Standard depencies
#include <unistd.h>
#include <exception>
#include <map>
#include <sstream>
#include <string>
#include <iostream>

// SDL dependencies
#include "SDL/SDL.h"
#include "SDL_ttf/SDL_ttf.h"

// Project dependencies
#include "characterview.h"
#include "commonloader.h"
#include "gamefont.h"
#include "gamelevel.h"
#include "gametimer.h"
#include "keyboardinput.h"
#include "playercontroller.h"
#include "point2d.h"
#include "screenview.h"
#include "tinyxml2.h"

//
// Constructor
//
CGame::CGame() :
    m_quit(false),
    m_inverseFrameRateCap(0.0),
    m_timeSlice(0.0)
{
    // Start SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        throw(std::runtime_error("SDL failed during Init"));
    }
    if(TTF_Init() == -1)
    {
        throw(std::runtime_error("TTF failed during Init"));
    }
}

//
// Destructor
//
CGame::~CGame()
{
    Cleanup();
    
    // exit SDL
    TTF_Quit();
    SDL_Quit();
}

//
// Create an animation file
//
void CGame::SaveCharacter(const std::string & fileName)
{
/*
    using namespace tinyxml2;
    
    XMLDocument characterDoc;
    
    XMLNode * characterNode = characterDoc.InsertEndChild(characterDoc.NewElement("Character"));
    characterNode->ToElement()->SetAttribute("name", "Erin");
    
    // image layers
    XMLNode * layersNode = characterNode->InsertEndChild(characterDoc.NewElement("Layers"));
    
    XMLNode * layer1 = layersNode->InsertEndChild(characterDoc.NewElement("Layer"));
    layer1->ToElement()->SetAttribute("image", "CharacterLayers/misc_shadow.png");
    
    XMLNode * layer2 = layersNode->InsertEndChild(characterDoc.NewElement("Layer"));
    layer2->ToElement()->SetAttribute("image","CharacterLayers/body_caucasian.png");
    
    XMLNode * layer3 = layersNode->InsertEndChild(characterDoc.NewElement("Layer"));
    layer3->ToElement()->SetAttribute("image", "CharacterLayers/cloths_blackdress.png");
    
    XMLNode * layer4 = layersNode->InsertEndChild(characterDoc.NewElement("Layer"));
    layer4->ToElement()->SetAttribute("image", "CharacterLayers/eyes_brown.png");
    
    XMLNode * layer5 = layersNode->InsertEndChild(characterDoc.NewElement("Layer"));
    layer5->ToElement()->SetAttribute("image", "CharacterLayers/misc_roundglasses.png");
    
    XMLNode * layer6 = layersNode->InsertEndChild(characterDoc.NewElement("Layer"));
    layer6->ToElement()->SetAttribute("image", "CharacterLayers/hair_longbrown.png");
    
    XMLNode * layer7 = layersNode->InsertEndChild(characterDoc.NewElement("Layer"));
    layer7->ToElement()->SetAttribute("image", "CharacterLayers/misc_femaledetails.png");
    
    XMLNode * layer8 = layersNode->InsertEndChild(characterDoc.NewElement("Layer"));
    layer8->ToElement()->SetAttribute("image", "CharacterLayers/misc_shoes.png");
    
    // Position
    XMLNode * position = characterNode->InsertEndChild(characterDoc.NewElement("Position"));
    position->ToElement()->SetAttribute("X", 200);
    position->ToElement()->SetAttribute("Y", 200);

    // Animations
    XMLNode * animations = characterNode->InsertEndChild(characterDoc.NewElement("Animations"));
    
    XMLNode * animation1 = animations->InsertEndChild(characterDoc.NewElement("Animation"));
    animation1->ToElement()->SetAttribute("animation", "Animations/CharacterAnimations/WalkUp.xml");
    
    XMLNode * animation2 = animations->InsertEndChild(characterDoc.NewElement("Animation"));
    animation2->ToElement()->SetAttribute("animation", "Animations/CharacterAnimations/WalkDown.xml");
    
    XMLNode * animation3 = animations->InsertEndChild(characterDoc.NewElement("Animation"));
    animation3->ToElement()->SetAttribute("animation", "Animations/CharacterAnimations/WalkLeft.xml");
    
    XMLNode * animation4 = animations->InsertEndChild(characterDoc.NewElement("Animation"));
    animation4->ToElement()->SetAttribute("animation", "Animations/CharacterAnimations/WalkRight.xml");
    
    XMLNode * animation5 = animations->InsertEndChild(characterDoc.NewElement("Animation"));
    animation5->ToElement()->SetAttribute("animation", "Animations/CharacterAnimations/StandUp.xml");
    
    XMLNode * animation6 = animations->InsertEndChild(characterDoc.NewElement("Animation"));
    animation6->ToElement()->SetAttribute("animation", "Animations/CharacterAnimations/StandDown.xml");
    
    XMLNode * animation7 = animations->InsertEndChild(characterDoc.NewElement("Animation"));
    animation7->ToElement()->SetAttribute("animation", "Animations/CharacterAnimations/StandLeft.xml");
    
    XMLNode * animation8 = animations->InsertEndChild(characterDoc.NewElement("Animation"));
    animation8->ToElement()->SetAttribute("animation", "Animations/CharacterAnimations/StandRight.xml");
    
    
    characterDoc.Print();
    characterDoc.SaveFile(fileName.c_str());
    characterDoc.PrintError();
    std::cout << "Should have saved: " << fileName << std::endl;
    */
}

//
// Initialize data members
//
void CGame::Initialize()
{
    m_upFont.reset(new CGameFont(std::string("Fonts/Arial.ttf"), 12));
    m_upFrameTimer.reset(new CGameTimer());
    
    // Setup screen
    m_upScreenView.reset(new N_ScreenView::CScreenView());
    m_upScreenView->Initialize();
    
    // Setup the level
    m_spLevel = N_CommonLoader::LoadLevel(std::string("LevelData/TestLevel.tmx"));
    
    // Setup player
    m_upPlayerController.reset(new CPlayerController());
    m_upPlayerController->LoadPlayer();
    
    // Connect the level view objects to the screen
    m_upScreenView->LoadLevel(m_spLevel, m_upPlayerController->GetCharacterView());
    
    // Setup input
    m_spKeyboardInput = std::make_shared<CKeyboardInput>();
    
    //SetFrameRateCap(60.0);
    //SaveCharacter("./CharacterData/Erin.xml");

}

//
// Destroy data members
//
void CGame::Cleanup()
{
    m_upPlayerController.reset(nullptr);
    m_upScreenView.reset(nullptr);
    m_upFont.reset(nullptr);
}

//
// Set a value to cap the frame rate at
// this should be a value in frames per second
//
void CGame::SetFrameRateCap(double frameRateCap)
{
    m_inverseFrameRateCap = 1000.0 / frameRateCap;
}

//
// Return the frame rate cap in a value of frames per second
//
double CGame::GetFrameRateCap()const
{
    return 1000.0 / m_inverseFrameRateCap;
}

//
// Show the frame rate in the upper left corner for debugging
//
void CGame::DisplayFrameRate()
{
    SDL_Color textColor = {255, 255, 255};
    std::stringstream message;
    double frameRate = 0.0;
    if(m_timeSlice > 0.0)
    {
        frameRate = 1.0 / m_timeSlice;
    }
    message << "FPS: " << frameRate;
    m_upScreenView->WriteMessage(message.str(), CPoint2D<int>(3,2), m_upFont->GetFont(), textColor);
}

//
// Display the player's current position
//
void CGame::DisplayPlayerPosition()
{
    SDL_Color textColor = {255, 255, 255};
    std::stringstream message;
    
    CPoint2D<int> position = m_upPlayerController->GetCharacterView().lock()->GetPosition();

    message << "Player Position: X: " << position.X() << "  Y: " << position.Y();
    m_upScreenView->WriteMessage(message.str(), CPoint2D<int>(3,2), m_upFont->GetFont(), textColor);
}

//
// Process input events
//
void CGame::HandleInput()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            m_quit = true;
        }
        else
        {
            m_spKeyboardInput->HandleInput(event);
        }
    }
    
    m_upPlayerController->HandleInput(m_spKeyboardInput);
}

//
// Calculate how long this frame took to run
//
void CGame::CalculateTimeSlice()
{
    // calculate the actual frame rate
    double frameTime = static_cast<double>(m_upFrameTimer->GetTicks());
    m_timeSlice = frameTime / 1000.0;
}

//
// TimeSlice for updates
//
double CGame::GetTimeSlice()const
{
    return m_timeSlice;
}

//
// Play the game
//
void CGame::Play()
{    
    while(!m_quit)
    {
        m_upFrameTimer->Start();
        
        HandleInput();

        // Update the game assets
        m_upPlayerController->Update(GetTimeSlice(), m_spLevel->GetCollisionData());

        // Blit to the screen surface
        m_upScreenView->ClearScreen();
        m_upScreenView->DrawViews();
        m_upScreenView->DrawCollisionData(m_spLevel->GetCollisionData());
        m_upScreenView->DrawBox(m_upPlayerController->GetCollisionBounds());
    
        DisplayFrameRate();
        //DisplayPlayerPosition();
        
        // Update the actual screen
        m_upScreenView->Display();

        CalculateTimeSlice();
    }
}












