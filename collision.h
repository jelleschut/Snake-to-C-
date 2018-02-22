#ifndef COLLISION_H
#define COLLISION_H

#include "fsm.h"

EVENTS borderCollision();
EVENTS foodCollision();
EVENTS selfCollision();
EVENTS collisionChecker();
EVENTS foodSpawnCollision();

int foodNoCollisionY();
int foodNoCollisionX();

#endif // COLLISION_H
