#include "snake.h"

static enum KEY MovGeneral;
static enum KEY MovAux;
static double velocity;
static SnakeBody snake;
static ObjectList listObjects;
static Object fruit;
extern enum STATE GameState;
extern int counter;

// loads xpm
extern uint8_t *snakeM;
extern xpm_image_t imgSnake;


extern uint8_t *wall;
extern xpm_image_t imgWall;

void MenuStarter(){

  MovGeneral = DOWN;
  snake.y = 40;
  snake.bodySize = 5;
  snake.x = 40;
  snake.bodyType = HEAD;
  velocity = 48;
  fruit.RectanglePixelSize = 48;
  fruit.topLeftPixelPosX = 200;
  fruit.topLeftPixelPosY = 200;
  fruit.type = FRUIT;
  listObjects.Object_entry = fruit;
}

void InterruptHandlerTimer(){
  updateMov();
  if(counter % 48 == 0){
    moveSnake();
  }
  
  drawSnake();
  drawObjects();
}

void drawSnake() {
  switch (MovGeneral)
  {
  case UP:
    break;
  
  case DOWN:
    break;

  case LEFT:
    break;
    
  case RIGHT:

    break;    

  default:
    break;
  }

  draw_pix_map(snake.x ,snake.y,snakeM,imgSnake);

  for(int i = 0; i < snake.bodySize; i++) {
    draw_pix_map(snake.bodyX[i],snake.bodyY[i],snakeM,imgSnake);
  }

}

void drawObjects() {
  uint8_t *map;
  xpm_image_t img;
  map = xpm_load(wall_xpm,XPM_8_8_8_8,&img);
  draw_pix_map(fruit.topLeftPixelPosX,fruit.topLeftPixelPosY,wall,imgWall);
}

void moveSnake() {


  switch (MovGeneral)
  {
  case UP:
    snake.y -= velocity;
    break;
  
  case DOWN:
    snake.y += velocity;
    break;

  case LEFT:
    snake.x -= velocity;
    break;
    
  case RIGHT:
    snake.x += velocity;
    break;    

  default:
    break;
  }

  

  int flag = CheckColisions();

  if(flag == 1){
      flag++;
    }

    snake.bodyX[0] = snake.x;
    snake.bodyY[0] = snake.y;
    for (int i = snake.bodySize; i > 0; i--)
    {
      snake.bodyX[i] = snake.bodyX[i - 1];
      snake.bodyY[i] = snake.bodyY[i - 1];
    }
}

int CheckColisions(){
  //fruit colision
  if(CheckSingleColision(&snake,&fruit)==1){
      snake.bodySize++;
      return 1;//1 is only fruit colision
  }
  return 0;

  //other colision
}

int CheckSingleColision(SnakeBody *snake,Object *object){
  if (snake->x < object->topLeftPixelPosX + object->RectanglePixelSize && 
  snake->x > object->topLeftPixelPosX && 
  snake->y < object->topLeftPixelPosY + object->RectanglePixelSize && 
  snake->y  > object->topLeftPixelPosY){
    return 1;
  }
  return 0;
}

void InterruptHandlerKBC(enum KEY k){
  if(k == ENTER) {
    return;
  }
  if(k == ESC) {
    GameState = PAUSE;
    return;
  }
  MovAux = k;
}

void updateMov(){
  MovGeneral = MovAux;
}
