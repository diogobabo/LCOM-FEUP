#include "menu.h"

int option = 0;

static int cleanX = 0;
static int cleanY = 0;

extern enum STATE GameState;
extern mouseInfo mouse;

// loads xpm
extern uint8_t *menuPlay;
extern xpm_image_t imgMenuPlay;

extern uint8_t *menuExit;
extern xpm_image_t imgMenuExit;

extern uint8_t *menu;
extern xpm_image_t imgMenu;

extern uint8_t *cursor;
extern xpm_image_t imgCursor;


void MenuMouseHandler() {
  if(mouse.delta_x >= 1152) {
    mouse.delta_x = 1151;
  }
  else if(mouse.delta_x < 0) {
    mouse.delta_x = 0;
  }
  if(mouse.delta_y >= 864) {
    mouse.delta_y = 863;
  }
  else if(mouse.delta_y < 0) {
    mouse.delta_y = 0;
  }
  if(mouse.delta_x > 490 && mouse.delta_y > 515 &&  mouse.delta_x < 700 && mouse.delta_y < 582) {
    option = 1;
  }
  else if(mouse.delta_x > 497 && mouse.delta_y > 636 && mouse.delta_x < 698 && mouse.delta_y < 720) {
    option = 2;
  }
  else {
    option = 0;
  }
  changeState();
}

void changeState() {
  if(option == 1 && mouse.lb) {
    mouse.lb = false;
    GameState = PLAY_SOLO;
  }
  else if(option == 2 && mouse.lb) {
    mouse.lb = false;
    GameState = EXIT;
  }
}

void drawDefMenu() {
  draw_pix_map(0,0,menu,imgMenu);
}
void drawCursor() {
  cleanX = mouse.delta_x;
  cleanY = mouse.delta_y;
  draw_pix_map(mouse.delta_x,mouse.delta_y,cursor,imgCursor);
}
void MenuTimerHandler() {
  cleanMenuBG();
  drawMenu();
  drawCursor();
}

void cleanMenuBG() {
  cleanBG(490,510,400,400,imgMenu,menu);
  cleanBG(cleanX,cleanY,imgCursor.width,imgCursor.height,imgMenu,menu);
}
void drawMenu() {
  if(option == 1)  {
    draw_pix_map(490,514,menuPlay,imgMenuPlay);
  }
  else if(option == 2) {
    draw_pix_map(497,640,menuExit,imgMenuExit);
  }
}
