#include "menu.h"

int option = 0;

extern enum STATE GameState;

// loads xpm
extern uint8_t *menuPlay;
extern xpm_image_t imgMenuPlay;

extern uint8_t *menuExit;
extern xpm_image_t imgMenuExit;



void MenuTimerHandler() {
  drawMenu(option);
}

void MenuHandlerKBC(enum KEY k) {
  switch (k)
  {
  case DOWN1:
    if(option == 1) {
      option = 1;
    }
    else {
      option++;
    }
    break;
  
  case UP1:
    if(option == 0) {
      option = 0;
    }
    else {
      option--;
    }
    break;
  
  case ENTER1:
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
}
