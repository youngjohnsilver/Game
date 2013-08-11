//
//  gametile.cpp
//  Game
//
//  Created by John Theiss on 7/25/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#include "gametile.h"

// Project dependencies
#include "gameassert.h"
#include "gameimage.h"
#include "screenview.h"

using N_GameAssert::GameAssert;
using N_ScreenView::ApplySurface;
using N_ScreenView::ConvertToRect;

//
// Constructor
//
CGameTile::CGameTile(
    const STileData & data,
    const int tileID,
    const CPoint2D<int> & worldPosition,
    const CPoint2D<int> & tileSetPosition) :
        m_data(data),
        m_tileID(tileID),
        m_worldPosition(worldPosition),
        m_tileSetPosition(tileSetPosition)
{
}

//
// View interface
//
void CGameTile::Draw(SDL_Surface * drawSurface, const CCamera & camera)const
{
    GameAssert(nullptr != drawSurface, std::string("drawSurface is nullptr in CGameTile::Draw"));
    
    SBoundingBox collisionBox;
    collisionBox.m_position.X() = m_worldPosition.X() + m_data.m_width / 2;
    collisionBox.m_position.Y() = m_worldPosition.Y() + m_data.m_height / 2;
    collisionBox.m_width = m_data.m_width;
    collisionBox.m_height = m_data.m_height;
    if(camera.IsOnScreen(collisionBox))
    {
        CPoint2D<int> screenPosition = camera.WorldToScreenTransform(GetWorldPosition());
        SDL_Rect clipRect = ConvertToRect(GetClipRect());
        ApplySurface(screenPosition, m_data.m_tileSet->GetSurface(), drawSurface, &clipRect);
    }
}

//
// Accessors
//
std::weak_ptr<const CGameImage> CGameTile::GetTileSet()const
{
    return m_data.m_tileSet;
}

CPoint2D<int> CGameTile::GetWorldPosition()const
{
    return m_worldPosition;
}

//
// Generate a clip rect that specifies this tile in the tileSet image
//
SBoundingBox CGameTile::GetClipRect()const
{
    SBoundingBox clipRect = { m_tileSetPosition, m_data.m_width, m_data.m_height };
    return clipRect;
}
