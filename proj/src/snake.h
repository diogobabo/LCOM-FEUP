#ifndef _PLAY_H
#define _PLAY_H

#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>
#include "devices/graphics.h"
#include "xpms/snake.xpm"
#include "xpms/wall.xpm"
#include "kbcKeys.h"

#define PIXELOFFSET 48
#define SNAKEMAXSIZE 864
enum SnakeBodyType{
  HEAD,
  BODY,
  TAIL,
  NULLBODY
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
  int y;

  int x;

  int bodySize;

  int bodyX[1000];

  int bodyY[1000];

  enum SnakeBodyType bodyType;

}SnakeBody;

void InterruptHandlerTimer();

void MenuStarter();

void drawSnake();

void moveSnake();

void InterruptHandlerKBC(enum KEY k);

void drawObjects();

int CheckColisions();

int CheckSingleColision(SnakeBody *snake,Object *object);//1 if true 0 if false

void updateMov();

#endif
