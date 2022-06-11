#include "pause.h"

extern enum STATE GameState;

// loads xpm
extern uint8_t *BoardMenu;
extern xpm_image_t imgBoard;


void BoardTimerHandler() {
}

void BoardHandlerKBC(enum KEY k) {
  switch (k)
  {
  case ESC:
    GameState = MENU;
    break;
  default:
    break;
  }
}

void drawDefBoard() {
  draw_pix_map(0,0,BoardMenu,imgBoard);
}

void drawBoard() {
}
