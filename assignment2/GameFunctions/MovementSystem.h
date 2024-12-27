#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include "../Entity.h"
#include "../Vec2.h"
#include <memory>

void processPlayerMovement(std::shared_ptr<Entity> e, float speed);
bool isDiagonalMovement(std::shared_ptr<Entity> e);
void processDiagonalMovement(std::shared_ptr<Entity> e, float speed);
void processStraightMovement(std::shared_ptr<Entity> e, float speed);
void processNonPlayerMovement(std::shared_ptr<Entity> e);

#endif // MOVEMENT_SYSTEM_H
