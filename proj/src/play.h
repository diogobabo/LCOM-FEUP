#ifndef _PLAY_H
#define _PLAY_H

#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>
#include "graphics.h"

enum SNAKEBODYIDENTITY{
  HEAD,
  BODY,
  TAIL
};

enum MOVIMENT{
  UP,
  DOWN,
  LEFT,
  RIGHT
};

struct SnakeBody
{
  int topLeftPixelPosY;
  int topLeftPixelPosx;
  int snakeRectanglePixelSize;
  int snakSize;
  struct SnakeBody* nextBody;
  enum MOVIMENT direction;
  enum SNAKEBODYIDENTITY bodyType;
};

void InterruptHandlerTimer();
void MenuStarter();

#endif
