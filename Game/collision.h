//
//  collision.h
//  Game
//
//  Created by John Theiss on 7/30/13.
//  Copyright (c) 2013 John Theiss. All rights reserved.
//

#ifndef Game_collision_h
#define Game_collision_h

// Forward declarations
struct SBoundingBox;

namespace N_Collision
{

bool Collides(const SBoundingBox & box1, const SBoundingBox & box2);

}

#endif
