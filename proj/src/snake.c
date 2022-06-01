#include "snake.h"

static enum Movement MovGeneral;
static double velocity;
static Snake snake;

void MenuStarter(){
  MovGeneral = DOWN;
  snake.topLeftPixelPosY = 20;
  snake.topLeftPixelPosX = 20;
  snake.snakeRectanglePixelSize = 50; 
  snake.snakeSize = 1;
  snake.bodyType = HEAD;
  snake.nextBody = NULL;
  velocity = 1;
}

void InterruptHandlerTimer(){
  moveSnake();
  drawSnake();
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
  return;
  if(snake.nextBody == NULL){
    return;
  }

  Snake *nextSnake = snake.nextBody;

  while (1)
  {
    draw_pix_map(nextSnake->topLeftPixelPosX,nextSnake->topLeftPixelPosY,map,img);

    if(nextSnake->nextBody == NULL){
      break;
    }
    nextSnake = nextSnake->nextBody;
  }


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
  return;
  if(snake.nextBody == NULL){
      return;
  }

  Snake *nextSnake = snake.nextBody;
  Snake *lastSnake = &snake;

  while (1)
  {
    nextSnake->topLeftPixelPosX = lastSnake->topLeftPixelPosX;
    nextSnake->topLeftPixelPosY = lastSnake->topLeftPixelPosY;

    lastSnake = nextSnake;

    if(nextSnake->nextBody == NULL){
      break;
    }
    nextSnake = nextSnake->nextBody;
  }

}

void InterruptHandlerKBC(enum Movement mov){
  MovGeneral = mov;
}
