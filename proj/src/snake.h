#ifndef _PLAY_H
#define _PLAY_H

#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>
#include "devices/graphics.h"
#include "xpms/up.xpm"
#include "xpms/left.xpm"
#include "xpms/down.xpm"
#include "xpms/right.xpm"
#include "xpms/wall.xpm"
#include "xpms/bgGame.xpm"
#include "xpms/fruit.xpm"
#include "xpms/bodySnake.xpm"
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
  int x;

  int y;

  enum ObjectType type;

  bool active;

}Object;


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

void spawnFruits();

void drawSnake();

void moveSnake();

void InterruptHandlerKBC(enum KEY k);

void drawObjects();

void drawBG();

int CheckColisions();

int CheckSingleColision(SnakeBody *snake,Object *object);//1 if true 0 if false

void updateMov();

void cleanAllBG();

void InterruptHandlerMouse();

bool checkFruit(int x, int y);

#endif
