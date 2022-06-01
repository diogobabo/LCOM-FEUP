#ifndef _PLAY_H
#define _PLAY_H

#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>
#include "devices/graphics.h"
#include "xpms/play.xpm"
#include "xpms/snake.xpm"
#include "xpms/wall.xpm"

enum SnakeBodyType{
  HEAD,
  BODY,
  TAIL,
  NULLBODY
};

enum Movement{
  UP,
  DOWN,
  LEFT,
  RIGHT
};

enum ObjectType{
  FRUIT,
  BLOCK
};

typedef struct Object_t
{
  int topLeftPixelPosY;

  int topLeftPixelPosX;

  int RectanglePixelSize;

  enum ObjectType type;

}Object;

typedef struct ObjectList_t {
    Object Object_entry;
    struct ObjectList_t *Object_next;
}ObjectList;

typedef struct Snake_t
{
  int topLeftPixelPosY;

  int topLeftPixelPosX;

  int snakeRectanglePixelSize;

  int snakeSize;

  struct Snake_t* nextBody;

  enum SnakeBodyType bodyType;

}Snake;

void InterruptHandlerTimer();

void MenuStarter();

void drawSnake();

void drawMenu();

void moveSnake();

void InterruptHandlerKBC(enum Movement mov);

void drawObjects();

int CheckColisions();

int CheckSingleColision(int rect1topLx,int rect1topLy,int rect1BotRx,int rect1BotRy,int rect2topLx,int rect2topLy,int rect2BotRx,int rect2BotRy);//1 if true 0 if false

#endif
