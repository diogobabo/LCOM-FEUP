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
extern uint8_t *snakeUp;
extern xpm_image_t imgSnakeUp;

extern uint8_t *snakeLeft;
extern xpm_image_t imgSnakeLeft;

extern uint8_t *snakeRight;
extern xpm_image_t imgSnakeRight;

extern uint8_t *snakeDown;
extern xpm_image_t imgSnakeDown;


extern uint8_t *fruitI;
extern xpm_image_t imgFruit;

extern uint8_t *gameBG;
extern xpm_image_t imgGameBG;

extern uint8_t *snakeTail;
extern xpm_image_t imgSnakeTail;

void MenuStarter(){

  MovGeneral = DOWN;
  snake.y = 96;
  snake.bodySize = 0;
  snake.x = 96;
  snake.bodyType = HEAD;
  velocity = 48;
  fruit.RectanglePixelSize = 48;
  fruit.topLeftPixelPosX = 384;
  fruit.topLeftPixelPosY = 384;
  fruit.type = FRUIT;
  listObjects.Object_entry = fruit;
}

void InterruptHandlerTimer(){
  drawBG();
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
    draw_pix_map(snake.x ,snake.y,snakeUp,imgSnakeUp);
    break;
  
  case RIGHT:
    draw_pix_map(snake.x ,snake.y,snakeDown,imgSnakeDown);
    break;

  case LEFT:
    draw_pix_map(snake.x ,snake.y,snakeLeft,imgSnakeLeft);
    break;
    
  case DOWN:
    draw_pix_map(snake.x ,snake.y,snakeRight,imgSnakeRight);
    break;    

  default:
    break;
  }


  for(int i = 0; i < snake.bodySize; i++) {
    draw_pix_map(snake.bodyX[i],snake.bodyY[i],snakeTail,imgSnakeTail);
  }

}

void drawObjects() {
  draw_pix_map(fruit.topLeftPixelPosX,fruit.topLeftPixelPosY,fruitI,imgFruit);
}

void drawBG() {
   draw_pix_map(0,0,gameBG,imgGameBG);
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

  
  CheckColisions();

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
  /*if(CheckSingleColision(&snake,&fruit)==1){
      snake.bodySize++;
      return 1;//1 is only fruit colision
  }*/
  if(snake.x == fruit.topLeftPixelPosX && snake.y == fruit.topLeftPixelPosY) {
    snake.bodySize++;
  }
  return 0;
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
