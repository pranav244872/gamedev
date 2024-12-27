#include "MovementSystem.h"

void processPlayerMovement(std::shared_ptr<Entity> e, float speed) {
  if (isDiagonalMovement(e)) {
    processDiagonalMovement(e, speed);
  } else {
    processStraightMovement(e, speed);
  }
}

bool isDiagonalMovement(std::shared_ptr<Entity> e) {
  return (e->cInput->up && e->cInput->left) ||
         (e->cInput->up && e->cInput->right) ||
         (e->cInput->down && e->cInput->left) ||
         (e->cInput->down && e->cInput->right);
}

void processDiagonalMovement(std::shared_ptr<Entity> e, float speed) {
  if (e->cInput->up && e->cInput->left) {
    e->cTransform->pos += Vec2(-speed, -speed);
  } else if (e->cInput->up && e->cInput->right) {
    e->cTransform->pos += Vec2(speed, -speed);
  } else if (e->cInput->down && e->cInput->left) {
    e->cTransform->pos += Vec2(-speed, speed);
  } else if (e->cInput->down && e->cInput->right) {
    e->cTransform->pos += Vec2(speed, speed);
  }
}

void processStraightMovement(std::shared_ptr<Entity> e, float speed) {
  if (e->cInput->up) {
    e->cTransform->pos.y -= speed;
  } else if (e->cInput->down) {
    e->cTransform->pos.y += speed;
  } else if (e->cInput->left) {
    e->cTransform->pos.x -= speed;
  } else if (e->cInput->right) {
    e->cTransform->pos.x += speed;
  }
}

void processNonPlayerMovement(std::shared_ptr<Entity> e) {
  e->cTransform->pos += e->cTransform->velocity;
}
