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
  snake.lastX = snake.topLeftPixelPosX;
  snake.lastY = snake.topLeftPixelPosY;
  snake.snakeRectanglePixelSize = 48; 
  snake.snakeSize = 1;
  snake.bodyType = HEAD;

  Snake *s = malloc(sizeof(Snake));

  s->topLeftPixelPosY = 12;
  s->topLeftPixelPosX = 20;
  s->lastX = s->topLeftPixelPosX;
  s->lastY = s->topLeftPixelPosY;
  s->snakeRectanglePixelSize = 48; 
  s->snakeSize = 1;
  s->bodyType = BODY;
  s->nextBody = NULL;

  snake.nextBody = s;

  velocity = 1;
  fruit.RectanglePixelSize = 48;
  fruit.topLeftPixelPosX = 200;
  fruit.topLeftPixelPosY = 200;
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

    if(nextSnake->nextBody == NULL || nextSnake->nextBody->bodyType == NULLBODY){
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
    snake.lastX = snake.topLeftPixelPosX;
    snake.lastY = snake.topLeftPixelPosY;
    snake.topLeftPixelPosY -= velocity;
    break;
  
  case DOWN:
    snake.lastX = snake.topLeftPixelPosX;
    snake.lastY = snake.topLeftPixelPosY;
    snake.topLeftPixelPosY += velocity;
    break;

  case LEFT:
    snake.lastX = snake.topLeftPixelPosX;
    snake.lastY = snake.topLeftPixelPosY;
    snake.topLeftPixelPosX -= velocity;
    break;
    
  case RIGHT:
    snake.lastX = snake.topLeftPixelPosX;
    snake.lastY = snake.topLeftPixelPosY;
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

  if(flag == 1){
    flag++;
  }
/*vejam este loop para mudar as cenas da cobra*/
  while (1)
  {
    nextSnake->lastX = nextSnake->topLeftPixelPosX;
    nextSnake->lastY = nextSnake->topLeftPixelPosY;

    nextSnake->topLeftPixelPosX = lastSnake->lastX;
    nextSnake->topLeftPixelPosY = lastSnake->lastY;

    lastSnake = nextSnake;

    if(nextSnake->nextBody == NULL){
      break;
    }
    nextSnake = nextSnake->nextBody;
  }

}

int CheckColisions(){
  //fruit colision
  if(CheckSingleColision(&snake,&fruit)==1){
      return 1;//1 is only fruit colision
  }
  return 0;

  //other colision
}

int CheckSingleColision(Snake *snake,Object *object){
  /*vcs sao uns burros*/
  if (snake->topLeftPixelPosX < object->topLeftPixelPosX + object->RectanglePixelSize && 
  snake->topLeftPixelPosX + snake->snakeRectanglePixelSize > object->topLeftPixelPosX && 
  snake->topLeftPixelPosY < object->topLeftPixelPosY + object->RectanglePixelSize && 
  snake->topLeftPixelPosY + snake->snakeRectanglePixelSize > object->topLeftPixelPosY){
    return 1;
  }
  /*
  if (rect1topLx < rect2BotRx && rect1BotRx > rect2topLx && rect1topLy < rect2BotRy && rect1BotRy > rect2topLy){
    return 1;
  }
  */
  return 0;
}

void InterruptHandlerKBC(enum Movement mov){
  MovGeneral = mov;
}
