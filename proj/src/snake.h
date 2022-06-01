#ifndef _PLAY_H
#define _PLAY_H

#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>
#include "devices/graphics.h"
#include "xpms/play.xpm"
#include "xpms/snake.xpm"

enum SnakeBodyType{
  HEAD,
  BODY,
  TAIL
};

enum Movement{
  UP,
  DOWN,
  LEFT,
  RIGHT
};

typedef struct Snake
{
  int topLeftPixelPosY;

  int topLeftPixelPosX;

  int snakeRectanglePixelSize;

  int snakeSize;

  struct Snake* nextBody;

  enum SnakeBodyType bodyType;

}Snake;

void InterruptHandlerTimer();

void MenuStarter();

void drawSnake();

void drawMenu();

void moveSnake();

void InterruptHandlerKBC(enum Movement mov);

#endif
