//
//  gametile.h
//  Game
//
//  Created by John Theiss on 7/25/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#ifndef Game_gametile_h
#define Game_gametile_h

// Standard dependencies
#include <memory>

// Project dependencies
#include "boundingbox.h"
#include "iview.h"
#include "point2d.h"

// Forward declarations
class CGameImage;

//
// Data common to all tiles in a tile set
//
struct STileData
{
    std::shared_ptr<CGameImage> m_tileSet;
    int m_width;
    int m_height;
};

class CGameTile : public IView
{
public:
    CGameTile(
        const STileData & data,
        const int tileID,
        const CPoint2D<int> & worldPosition,
        const CPoint2D<int> & tileSetPosition);
    virtual ~CGameTile() = default;
    
    // view interface
    virtual void Draw(SDL_Surface * drawSurface, const CCamera & camera)const;
    
    std::weak_ptr<const CGameImage> GetTileSet()const;
    CPoint2D<int> GetWorldPosition()const;
    SBoundingBox GetClipRect()const;
    
private:
    STileData m_data;
    int m_tileID;
    CPoint2D<int> m_worldPosition;
    CPoint2D<int> m_tileSetPosition;
};

#endif
