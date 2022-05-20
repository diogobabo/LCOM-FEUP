// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>
#include "mouse.h"
#include "i8042.h"

// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int (mouse_test_packet)(uint32_t cnt) {
  extern uint8_t scancode;
  struct packet pack;
  int ipc_status,r;
  message msg;
  bool byteTwo = false;
  bool byteThree = false;
  extern int flag;
  uint8_t bit_no;

  if (mouse_enable_data_reporting() != 0) {return 1;}
  if (mouse_subscribe_int(&bit_no)!=0) {return 1;}

   uint32_t irq_set = BIT(bit_no);

  while(cnt > 0){
      if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
        printf("driver_receive failed with: %d", r);
        continue;
      }
      if (is_ipc_notify(ipc_status)) {
        switch (_ENDPOINT_P(msg.m_source)) {
          case HARDWARE: 
            if (msg.m_notify.interrupts & irq_set) {
              mouse_ih();
              if(flag == 0) {
                if (!byteTwo && !byteThree && (scancode & BIT(3))){
                  pack.bytes[0] = scancode;
                  byteTwo = true;
                }
                else if (byteTwo && (!byteThree)) {
                  byteTwo = false;
                  byteThree = true;
                  pack.bytes[1] = scancode;
                }
                else if (byteThree && (!byteTwo)) {
                  pack.bytes[2] = scancode;
                  byteThree = false;
                  cnt--;
                  mouse_set_packet(&pack);
                  mouse_print_packet(&pack);
                }
              }
            }
            break;
          default:
            break; 
        }
      }
  }

  if (mouse_unsubscribe_int()!=0) {return 1;}
  if (mouse_disable_data_reporting() != 0) {return 1;}
  
  
  return 0;
}
  
int (mouse_test_async)(uint8_t idle_time) {
    /* To be completed */
    printf("%s(%u): under construction\n", __func__, idle_time);
    return 1;
}

int (mouse_test_gesture)(uint8_t x_len, uint8_t tolerance) {
    /* To be completed */
    printf("%s: under construction\n", __func__);
    return 1;
}

int (mouse_test_remote)(uint16_t period, uint8_t cnt) {
    /* This year you need not implement this. */
    printf("%s(%u, %u): under construction\n", __func__, period, cnt);
    return 1;
}
