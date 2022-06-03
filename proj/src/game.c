#include "game.h"

enum STATE GameState;
uint8_t bit_timer;
uint8_t bit_kb;
uint8_t bit_m;
extern uint8_t scode;
extern int flag;
enum KEY key;
extern int counter;

// loads xpm
uint8_t *menuPlay;
xpm_image_t imgMenuPlay;

uint8_t *menuExit;
xpm_image_t imgMenuExit;

uint8_t *snakeM;
xpm_image_t imgSnake;


uint8_t *wall;
xpm_image_t imgWall;

void gameLoop() {
  int ipc_status;
  message msg;
  int r;
  int idx = 0;
  uint8_t array[2];
  uint32_t mask_timer = BIT(bit_timer);
  uint32_t mask_kb = BIT(bit_kb);
  uint32_t mask_mouse = BIT(bit_m);
  int time = 0;

  loadAll();
  GameState = MENU;
  MenuStarter();

  while(scode != ESCSCAN) { 
        if( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
          printf("driver_receive failed with: %d", r);
          continue;
        }
        if (is_ipc_notify(ipc_status)) { 
            switch (_ENDPOINT_P(msg.m_source)) {
              case HARDWARE: 
                /* Timer Interrupts */
                if (msg.m_notify.interrupts & mask_timer) { 
                  timer_int_handler();
                  switchBuffer();
                  InterruptRouter(TIMER);
                  if(counter % 60 == 0) {
                    time++;
                  }
                }
                /* Keyboard Interrupts */
                if(msg.m_notify.interrupts & mask_kb) {
                  kbc_ih();
                  if(flag == 0) {
                    if(idx == 0) {
                      array[idx] = scode;
                      if(scode == DEFSCAN) {
                        idx = 1;
                      }
                      else {
                        InterruptRouter(KBC);
                      }
                    }
                    else {
                      array[idx] = scode;
                      idx = 0;
                      InterruptRouter(KBC);
                    }
                  }

                }
                /* Mouse Interrupts */
                if (msg.m_notify.interrupts & mask_mouse) {
                  mouse_ih();
                  InterruptRouter(MOUSE);
                }
                break;
              default:
                break; 
            }
        }
  }
}


void InterruptRouter(enum DEVICE device){
  switch (GameState){
    case MENU:
      MenuIH(device);
      break;
    case PAUSE:
      PauseIH(device);
      break;
    case PLAY_SOLO:
      PlaySoloIH(device);
      break;
    case PLAY_MULTIPLAYER:
      PlayMultiplayerIH(device);
      break;
    case DEAD:
      DeadIH(device);
      break;
    case EXIT:
      break;
  }
}

void MenuIH(enum DEVICE device){
  switch (device)
  {
  case KBC:
    updateKBC();
    MenuHandlerKBC(key);
    break;
  
  case TIMER:
    MenuTimerHandler();
    break;

  default:
    break;
  }
  return;
}
void PauseIH(enum DEVICE device){
  return;
}
void PlaySoloIH(enum DEVICE device){
  switch (device) {
    case TIMER:
      InterruptHandlerTimer();
      break;
    case KBC:
      changePosition();
      break;
    default:
      break;
  }
}
void PlayMultiplayerIH(enum DEVICE device){
  return;
}
void DeadIH(enum DEVICE device){
  return;
}

void changePosition() {
    switch (scode)
    {
    case 0x50:
      InterruptHandlerKBC(DOWN);
      break;
    
    case 0x48:
      InterruptHandlerKBC(UP);
      break;

    case 0x4B:
      InterruptHandlerKBC(LEFT);
      break;

    case 0x4D:
      InterruptHandlerKBC(RIGHT);
      break;    
    default:
      break;
    }
}

void updateKBC(){
  switch (scode)
  {
  case 0x50: //ARROW DOWN
    key = DOWN1;
    break;
  
  case 0x48: //ARROW UP
    key = UP1;
    break;

  case 0x4B: //ARROW LEFT
    key = LEFT1;
    break;

  case 0x4D: //ARROW RIGHT
    key = RIGHT1;
    break;

  case 0x11: //W
    key = UP1;
    break;

  case 0x1F: //S
    key = DOWN1;
    break;

  case 0x1E: //A
    key = LEFT1;
    break;

  case 0X20: //D
    key = RIGHT1;
    break;

  case 0x1C: //ENTER
    key = ENTER1;
    break;
  case 0x01: //ESC
    key = ESC1;
    break;

  default:
    break;
  }
}

void loadAll() {
  menuPlay = xpm_load(play_menu,XPM_8_8_8_8,&imgMenuPlay);
  menuExit = xpm_load(exit_menu,XPM_8_8_8_8,&imgMenuExit);
  snakeM = xpm_load(snake_play,XPM_8_8_8_8,&imgSnake);
  wall = xpm_load(wall_xpm,XPM_8_8_8_8,&imgWall);
}
