#include "snake.h"

static enum Movement MovGeneral;
static double velocity;
static Snake snake;
static ObjectList listObjects;
static Object fruit;

void MenuStarter(){
  MovGeneral = DOWN;
  snake.topLeftPixelPosY = 60;
  snake.topLeftPixelPosX = 20;
  snake.snakeRectanglePixelSize = 48; 
  snake.snakeSize = 1;
  snake.bodyType = HEAD;

  Snake *s = malloc(sizeof(Snake));

  s->topLeftPixelPosY = 12;
  s->topLeftPixelPosX = 20;
  s->snakeRectanglePixelSize = 48; 
  s->snakeSize = 1;
  s->bodyType = NULLBODY;
  s->nextBody = NULL;

  snake.nextBody = s;

  velocity = 1;
  fruit.RectanglePixelSize = 48;
  fruit.topLeftPixelPosX = 140;
  fruit.topLeftPixelPosY = 140;
  fruit.type = FRUIT;
  listObjects.Object_entry = fruit;
}

void InterruptHandlerTimer(){
  moveSnake();
  drawSnake();
  drawObjects();
}

void drawMenu() {
  uint8_t *map;
  xpm_image_t img;
  map = xpm_load(play_car,XPM_8_8_8_8,&img);
  draw_pix_map(0,0,map,img);
}


void drawSnake() {
  uint8_t *map;
  xpm_image_t img;

  switch (MovGeneral)
  {
  case UP:
    map = xpm_load(snake_play,XPM_8_8_8_8,&img);
    break;
  
  case DOWN:
    map = xpm_load(snake_play,XPM_8_8_8_8,&img);
    break;

  case LEFT:
    map = xpm_load(snake_play,XPM_8_8_8_8,&img);
    break;
    
  case RIGHT:
    map = xpm_load(snake_play,XPM_8_8_8_8,&img);
    break;    

  default:
    break;
  }

  draw_pix_map(snake.topLeftPixelPosX,snake.topLeftPixelPosY,map,img);

  if(snake.nextBody == NULL){
    return;
  }

  Snake *nextSnake = snake.nextBody;

  if(nextSnake->bodyType == NULLBODY){
    return;
  }

  while (1)
  {
    draw_pix_map(nextSnake->topLeftPixelPosX,nextSnake->topLeftPixelPosY,map,img);

    if(nextSnake->nextBody == NULL){
      break;
    }
    nextSnake = nextSnake->nextBody;
  }
}

void drawObjects() {
  uint8_t *map;
  xpm_image_t img;
  map = xpm_load(wall_xpm,XPM_8_8_8_8,&img);
  draw_pix_map(fruit.topLeftPixelPosX,fruit.topLeftPixelPosY,map,img);
}

void moveSnake() {
  
  switch (MovGeneral)
  {
  case UP:
    snake.topLeftPixelPosY -= velocity;
    break;
  
  case DOWN:
    snake.topLeftPixelPosY += velocity;
    break;

  case LEFT:
    snake.topLeftPixelPosX -= velocity;
    break;
    
  case RIGHT:
    snake.topLeftPixelPosX += velocity;
    break;    

  default:
    break;
  }

  if(snake.nextBody == NULL){
      return;
  }

  int flag = CheckColisions();

  Snake *nextSnake = snake.nextBody;
  Snake *lastSnake = &snake;

  while (1)
  {
    if(flag == 1){
      
      if(nextSnake->bodyType == NULLBODY){
      Snake *s = malloc(sizeof(Snake));

      s->topLeftPixelPosY = 12;
      s->topLeftPixelPosX = 20;
      s->snakeRectanglePixelSize = 48; 
      s->snakeSize = 1;
      s->bodyType = BODY;
      s->nextBody = NULL;

    }
    }
    
    nextSnake->topLeftPixelPosX = lastSnake->topLeftPixelPosX;
    nextSnake->topLeftPixelPosY = lastSnake->topLeftPixelPosY;

    lastSnake = nextSnake;

    if(nextSnake->nextBody == NULL){
      break;
    }
    nextSnake = nextSnake->nextBody;
  }

}

int CheckColisions(){
  //fruit colision
  if(CheckSingleColision(snake.topLeftPixelPosX,snake.topLeftPixelPosY,snake.topLeftPixelPosX + snake.snakeRectanglePixelSize,snake.topLeftPixelPosY + snake.snakeRectanglePixelSize,fruit.topLeftPixelPosX,fruit.topLeftPixelPosY,fruit.topLeftPixelPosX + fruit.RectanglePixelSize,fruit.topLeftPixelPosY + fruit.RectanglePixelSize)==1){
      return 1;//1 is only fruit colision
  }
  return 0;

  //other colision
}

int CheckSingleColision(int rect1topLx,int rect1topLy,int rect1BotRx,int rect1BotRy,int rect2topLx,int rect2topLy,int rect2BotRx,int rect2BotRy){
  if (rect1topLx < rect2BotRx && rect1BotRx > rect2topLx && rect1topLy < rect2BotRy && rect1BotRy > rect2topLy){
    return 1;
  }
  return 0;
}

void InterruptHandlerKBC(enum Movement mov){
  MovGeneral = mov;
}
