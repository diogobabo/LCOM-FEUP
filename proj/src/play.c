#include "play.h"

static enum MOVIMENT MovGeneral;
static struct SnakeBody snake;
static double velocity;

void MenuStarter(){
  MovGeneral = LEFT;
  snake.topLeftPixelPosY = 500;
  snake.topLeftPixelPosx = 500;
  snake.snakeRectanglePixelSize = 50; 
  snake.snakSize = 1;
  snake.direction = LEFT;
  snake.bodyType = HEAD;
  snake.nextBody = NULL;
  velocity = 1;
}

void InterruptHandlerTimer(){

}
