//
//  characterview.h
//  Game
//
//  Created by John Theiss on 7/20/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#ifndef Game_characterview_h
#define Game_characterview_h

// Standard dependencies
#include <map>
#include <memory>
#include <string>
#include <vector>

// Project dependencies
#include "animationframe.h"
#include "iview.h"
#include "point2d.h"

// Forward declarations
class CGameImage;
class IAnimation;

struct SCharacterViewData
{
    std::vector<std::shared_ptr<CGameImage>> m_characterLayers;
    CPoint2D<int> m_position;
    int m_zLevel;
    std::string m_currentAnimationName;
    std::map<std::string, std::shared_ptr<IAnimation>> m_animations;
};

class CCharacterView : public IView
{
public:
    explicit CCharacterView(const SCharacterViewData & data);
    virtual ~CCharacterView();
    
    // view interface
    virtual void Draw(SDL_Surface * drawSurface, const CCamera & camera) const;
    
    void Update(const double timeSlice, const double frameRate);
    
    CPoint2D<int> GetPosition()const;
    int GetZLevel()const;
    void SetPosition(const CPoint2D<int> & position);

    std::vector<std::shared_ptr<CGameImage>> GetLayers()const;
    CAnimationFrame GetCurrentFrame()const;
    
    void SetCurrentAnimation(const std::string & animationName);
    void SetAnimations(const std::map<std::string, std::shared_ptr<IAnimation>> & animations);
    
private:
    SCharacterViewData m_data;
};

#endif
