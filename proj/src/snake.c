#include "snake.h"

static enum Movement MovGeneral;
static enum Movement MovAux;
static double velocity;
static SnakeBody snake[SNAKEMAXSIZE];
static ObjectList listObjects;
static Object fruit;
extern int counter;

// loads xpm
extern uint8_t *snakeM;
extern xpm_image_t imgSnake;


extern uint8_t *wall;
extern xpm_image_t imgWall;

void MenuStarter(){
  for(int x = 0; x< SNAKEMAXSIZE ; x++){
    snake[x].bodyType = NULLBODY;
    snake[x].lastX = 0;
    snake[x].lastY = 0;
    snake[x].x = 0;
    snake[x].y = 0;
  }

  MovGeneral = DOWN;
  snake[0].y = 2;
  snake[0].x = 1;
  snake[0].lastX = snake[0].x;
  snake[0].lastY = snake[0].y;
  snake[0].bodyType = HEAD;

  velocity = 1;
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

  draw_pix_map(snake[0].x * PIXELOFFSET,snake[0].y * PIXELOFFSET,snakeM,imgSnake);

}

void drawObjects() {
  uint8_t *map;
  xpm_image_t img;
  map = xpm_load(wall_xpm,XPM_8_8_8_8,&img);
  draw_pix_map(fruit.topLeftPixelPosX,fruit.topLeftPixelPosY,wall,imgWall);
}

void moveSnake() {

  snake[0].lastX = snake[0].x;
  snake[0].lastY = snake[0].y;

  switch (MovGeneral)
  {
  case UP:
    snake[0].y -= velocity;
    break;
  
  case DOWN:
    snake[0].y += velocity;
    break;

  case LEFT:
    snake[0].x -= velocity;
    break;
    
  case RIGHT:
    snake[0].x += velocity;
    break;    

  default:
    break;
  }

  

  int flag = CheckColisions();

  if(flag == 1){
      flag++;
    }
}

int CheckColisions(){
  //fruit colision
  if(CheckSingleColision(&snake[0],&fruit)==1){
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

void InterruptHandlerKBC(enum Movement mov){
  MovAux = mov;
}

void updateMov(){
  MovGeneral = MovAux;
}
