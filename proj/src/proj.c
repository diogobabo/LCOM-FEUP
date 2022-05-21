#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>
#include "keyboard.h"
#include "mouse.h"
#include "graphics.h"
#include "snake.h"


int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/proj/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/proj/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(proj_main_loop)(int argc, char* argv[]){
  extern uint8_t bit_timer;
  extern uint8_t bit_kb;
  extern uint8_t bit_m;

  if(timer_subscribe_int(&bit_timer) != 0) {
    return 1;
  }

  if(kb_subscribe(&bit_kb) != 0) {
    return 1;
  }

  if(mouse_subscribe_int(&bit_m) != 0) {
    return 1;
  }

  playSnakeLoop();


  if(timer_unsubscribe_int() != 0) {
    return 1;
  }

  if(kb_unsubscribe() != 0) {
    return 1;
  }

  if(mouse_unsubscribe_int() != 0) {
    return 1;
  }

  return 0;
}
