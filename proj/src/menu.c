#include "menu.h"

int option = 0;

extern enum STATE GameState;
extern mouseInfo mouse;

// loads xpm
extern uint8_t *menuPlay;
extern xpm_image_t imgMenuPlay;

extern uint8_t *menuExit;
extern xpm_image_t imgMenuExit;

extern uint8_t *cursor;
extern xpm_image_t imgCursor;

void MenuMouseHandler() {
  drawCursor();
}
void drawCursor() {
}
void MenuTimerHandler() {
}

void MenuHandlerKBC(enum KEY k) {
  switch (k)
  {
  case DOWN:
    if(option == 1) {
      option = 1;
    }
    else {
      option++;
    }
    break;
  
  case UP:
    if(option == 0) {
      option = 0;
    }
    else {
      option--;
    }
    break;
  
  case ENTER:
    if(option == 0) {
      GameState = PLAY_SOLO;
    }
    else if(option == 1) {
      GameState = EXIT;
    }
  default:
    break;
  }
}

void drawMenu(int opt) {
  switch (opt)
  {
  case 0:
    draw_pix_map(0,0,menuPlay,imgMenuPlay);
    break;
  
  case 1:
    draw_pix_map(0,0,menuExit,imgMenuExit);
    break;
  }
  draw_pix_map(mouse.delta_x,mouse.delta_y,cursor,imgCursor);
}
