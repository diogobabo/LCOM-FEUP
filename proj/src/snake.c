#include "snake.h"

static enum KEY MovGeneral;
static enum KEY MovAux;
static double velocity;
static SnakeBody snake;
extern enum STATE GameState;
extern int counter;
static Object array[1000];
static int numObjects = 0;

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
}

void spawnFruits() {
  bool canSpawn = true;
  int x,y;
  x = (rand() % 22) + 1;
  y = (rand() % 16) + 1;

  for(int i = 0; i < numObjects; i++) {
    if(x == array[i].x && y == array[i].y && array[i].active) {
      canSpawn = false;
    }
  }

  for(int i = 0; i < snake.bodySize; i++) {
    if(x == snake.bodyX[i] && y == snake.bodyY[i]) {
      canSpawn = false;
    }
  }

  if(x == snake.x && y == snake.y) {
    canSpawn = false;
  }

  if(canSpawn && (counter % 240 == 0)) {
    Object obj;
    obj.x = x;
    obj.y = y;
    obj.type = FRUIT;
    obj.active = true;
    array[numObjects] = obj;
    numObjects++;
  }
}

void InterruptHandlerTimer(){
  drawBG();
  CheckColisions();
  spawnFruits();
  if(counter % 4 == 0){
  updateMov();
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
    draw_pix_map(snake.bodyX[i] * PIXELOFFSET,snake.bodyY[i] *PIXELOFFSET,snakeTail,imgSnakeTail);
  }
}

void drawObjects() {
  for(int i = 0; i < numObjects; i++) {
    if(array[i].active) {
      draw_pix_map(array[i].x * PIXELOFFSET,array[i].y  * PIXELOFFSET,fruitI,imgFruit);
    }
  }
}

void drawBG() {
   draw_pix_map(0,0,gameBG,imgGameBG);
}

void moveSnake() {
  for (int i = snake.bodySize; i > 0; i--)
  {
    snake.bodyX[i] = snake.bodyX[i - 1];
    snake.bodyY[i] = snake.bodyY[i - 1];
  }
  snake.bodyX[0] = snake.x / PIXELOFFSET;
  snake.bodyY[0] = snake.y / PIXELOFFSET;


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

}

int CheckColisions(){
  for(int i = 0; i < numObjects; i++) {
    if((snake.x == array[i].x * PIXELOFFSET) && (snake.y == array[i].y * PIXELOFFSET) && (array[i].active) && (array[i].type == FRUIT)) {
      array[i].active = false;
      snake.bodySize++;
      return 0;
    }
    else if((snake.x == array[i].x * PIXELOFFSET) && (snake.y == array[i].y * PIXELOFFSET) && (array[i].active) && (array[i].type == BLOCK)) {
      GameState = EXIT;
      return 0;
    }
  }
  if(snake.x <= PIXELOFFSET - 1 || snake.x >= (23 * PIXELOFFSET) || snake.y <= PIXELOFFSET - 1 || snake.y >= ((17 * PIXELOFFSET) - 1)) {
      GameState = EXIT;
      return 0;
    }
  for(int i = 0; i < snake.bodySize; i++) {
    if((snake.x == snake.bodyX[i] * PIXELOFFSET) && (snake.y == snake.bodyY[i] * PIXELOFFSET)) {
      GameState = EXIT;
      return 0;
    }
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
  if(MovGeneral == LEFT && MovAux == RIGHT) {
    return;
  }
  else if(MovGeneral == RIGHT && MovAux == LEFT) {
    return;
  }
  else if(MovGeneral == UP && MovAux == DOWN) {
    return;
  }
  else if(MovGeneral == DOWN && MovAux == UP) {
    return;
  }
  else {
    MovGeneral = MovAux;
  }
}
