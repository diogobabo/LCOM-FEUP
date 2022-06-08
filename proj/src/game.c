#include "game.h"

enum STATE GameState;
uint8_t bit_timer;
uint8_t bit_kb;
uint8_t bit_m;
extern uint8_t scode;
extern uint8_t scancode;
extern int flag;
extern int flag_m;
enum KEY key;
struct packet pack;
extern int counter;
mouseInfo mouse;
extern int option;

// loads xpm
uint8_t *menuPlay;
xpm_image_t imgMenuPlay;

uint8_t *menuExit;
xpm_image_t imgMenuExit;

uint8_t *snakeDown;
xpm_image_t imgSnakeDown;

uint8_t *snakeUp;
xpm_image_t imgSnakeUp;


uint8_t *snakeLeft;
xpm_image_t imgSnakeLeft;


uint8_t *snakeRight;
xpm_image_t imgSnakeRight;

uint8_t *snakeTail;
xpm_image_t imgSnakeTail;


uint8_t *fruitI;
xpm_image_t imgFruit;

uint8_t *cursor;
xpm_image_t imgCursor;

uint8_t *resume;
xpm_image_t imgResume;

uint8_t *pauseExit;
xpm_image_t imgPauseExit;


uint8_t *gameBG;
xpm_image_t imgGameBG;



/* Actual Functions */

void gameLoop() {
  int ipc_status;
  message msg;
  int r;
  int idx = 0;
  int numPacket = 0;
  bool firstTimeMenu = true;
  bool firstTimeGame = true;
  uint8_t array[2];
  mouse.delta_x = 576;
  mouse.delta_y = 432;
  uint32_t mask_timer = BIT(bit_timer);
  uint32_t mask_kb = BIT(bit_kb);
  uint32_t mask_mouse = BIT(bit_m);
  int time = 0;

  loadAll();
  GameState = MENU;
  MenuStarter();

  while(GameState != EXIT) { 
        if( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
          printf("driver_receive failed with: %d", r);
          continue;
        }
        if (is_ipc_notify(ipc_status)) { 
            switch (_ENDPOINT_P(msg.m_source)) {
              case HARDWARE: 
                /* Timer Interrupts */
                if (msg.m_notify.interrupts & mask_timer) { 
                  if(firstTimeGame && GameState == PLAY_SOLO) {
                    drawBG();
                    firstTimeGame = false;
                    switchBuffer();
                  }
                  else if(firstTimeMenu && GameState == MENU) {
                    drawMenu(option);
                    firstTimeMenu = false;
                    switchBuffer();
                  }
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
                  if(flag_m == 0) {
                    if (numPacket == 0 && (scancode & BIT(3))){
                      pack.bytes[0] = scancode;
                      numPacket++;
                    }
                    else if (numPacket == 1) {
                      pack.bytes[1] = scancode;
                      numPacket++;
                    }
                    else if (numPacket == 2) {
                      pack.bytes[2] = scancode;
                      numPacket = 0;
                      mouse_set_packet(&pack);
                      mouse.delta_x += pack.delta_x;
                      mouse.delta_y -= pack.delta_y;
                      mouse.lb = pack.lb;
                      mouse.rb = pack.rb;
                      mouse.mb = pack.mb;
                    }
                  }
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

  case MOUSE:
    break;
  default:
    break;
  }
  return;
}
void PauseIH(enum DEVICE device){
  switch (device)
  {
  case TIMER:
    PauseTimerHandler();
    break;
  
  case KBC:
    updateKBC();
    PauseHandlerKBC(key);
    break;
  default:
    break;
  }
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
    case MOUSE:
      InterruptHandlerMouse();
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
  updateKBC(scode);
  InterruptHandlerKBC(key);
}

void updateKBC(){
  switch (scode)
  {
  case 0x50: //ARROW DOWN
    key = DOWN;
    break;
  
  case 0x48: //ARROW UP
    key = UP;
    break;

  case 0x4B: //ARROW LEFT
    key = LEFT;
    break;

  case 0x4D: //ARROW RIGHT
    key = RIGHT;
    break;

  case 0x11: //W
    key = UP;
    break;

  case 0x1F: //S
    key = DOWN;
    break;

  case 0x1E: //A
    key = LEFT;
    break;

  case 0X20: //D
    key = RIGHT;
    break;

  case 0x1C: //ENTER
    key = ENTER;
    break;
  case 0x01: //ESC
    key = ESC;
    break;
    
  default:
    break;
  }
}

void loadAll() {
  menuPlay = xpm_load(play_menu,XPM_8_8_8_8,&imgMenuPlay);
  menuExit = xpm_load(exit_menu,XPM_8_8_8_8,&imgMenuExit);
  snakeUp = xpm_load(snake_up,XPM_8_8_8_8,&imgSnakeUp);
  snakeDown = xpm_load(snake_down,XPM_8_8_8_8,&imgSnakeDown);
  snakeLeft = xpm_load(snake_left,XPM_8_8_8_8,&imgSnakeLeft);
  snakeTail = xpm_load(body_snake,XPM_8_8_8_8,&imgSnakeTail);
  snakeRight = xpm_load(snake_right,XPM_8_8_8_8,&imgSnakeRight);
  fruitI = xpm_load(game_fruit,XPM_8_8_8_8,&imgFruit);
  cursor = xpm_load(mouse_cursor,XPM_8_8_8_8,&imgCursor);
  pauseExit = xpm_load(exit_pause,XPM_8_8_8_8,&imgPauseExit);
  resume = xpm_load(resume_game,XPM_8_8_8_8,&imgResume);
  gameBG = xpm_load(game_bg,XPM_8_8_8_8,&imgGameBG);
}
