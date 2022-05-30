#include "snake.h"

static enum STATE GameState;

uint8_t bit_timer;
uint8_t bit_kb;
uint8_t bit_m;

void playSnakeLoop() {
  extern uint8_t scode;
  extern int flag;
  extern int counter;
  int ipc_status;
  message msg;
  int r;
  uint32_t mask_timer = BIT(bit_timer);
  uint32_t mask_kb = BIT(bit_kb);
  uint32_t mask_mouse = BIT(bit_m);
  int time = 0;

  

  if(video_set_graphics(0x14C) != 0) {
    printf("Error mapping mem");
    return;
  }

  if (mouse_enable_data_reporting() != 0) {
    printf("Error enabling mouse data");
    return;
  }

  if(timer_set_frequency(0, 60) != 0) {
    printf("Error changing freq");
    return;
  }
  GameState = PLAY_SOLO;
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
                  timer_int_handler();
                  InterruptRouter(TIMER);
                  if(counter % 60 == 0) {
                    time++;
                  }
                }
                /* Keyboard Interrupts */
                if(msg.m_notify.interrupts & mask_kb) {
                  kbc_ih(); 
                  InterruptRouter(KBC);
                }
                /* Mouse Interrupts */
                if (msg.m_notify.interrupts & mask_mouse) {
                  mouse_ih();
                  InterruptRouter(MOUSE);
                }
                if(time == 10) {
                  GameState = EXIT;
                }
                break;
              default:
                break; 
            }
        }
  }

  if(vg_exit() != 0) {
    printf("Error going back to text mode");
    return;
  }

  if (mouse_disable_data_reporting() != 0) {
    printf("Error Disabling Data");
    return;
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
