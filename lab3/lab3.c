#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>
#include "keyboard.h"

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)() {
  extern int flag;
  extern uint8_t scode;
  int ipc_status;
  message msg;
  int r;
  uint8_t bit_no;
  uint8_t arr[1];
  keyboard_subscribe_int(&bit_no);
  uint32_t irq_set = BIT(bit_no);
  while( scode != 0x81 ) { /* You may want to use a different condition */
        /* Get a request message. */
        if( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
          printf("driver_receive failed with: %d", r);
          continue;
        }
        if (is_ipc_notify(ipc_status)) { /* received notification */
            switch (_ENDPOINT_P(msg.m_source)) {
              case HARDWARE: /* hardware interrupt notification */
                
                if (msg.m_notify.interrupts & irq_set) { /* subscri ... process it */
                  kbc_ih();
                  if(flag == 0){

                    bool make = scode & BIT(7);/* cheking break code or make code*/
                    arr[0] = scode;
                    kbd_print_scancode(!make,1,arr);
                  }
                  
                }
                break;
              default:
                break; /* no other notifications expected: do nothi*/
            }
        }
  }
  keyboard_unsubscribe_int();

  return 0;
}

int(kbd_test_poll)() {
  uint8_t stat;
  uint8_t data;
  uint8_t arr[1];
  while(data !=  0x81)) {
    util_sys_inb(STAT_REG, &stat); /* assuming it returns OK */
    /* loop while 8042 output buffer is empty */
    uint8_t temp = stat & (KBC_OBF | KBC_AUX);
    if(temp == 1) {
      util_sys_inb(OUT_BUF, &data); /* ass. it returns OK */
      if ((stat & (ERROR_PARITY | ERROR_TIMEOUT)) == 0 )
        bool make = scode & BIT(7);/* cheking break code or make code*/
        arr[0] = scode;
        kbd_print_scancode(!make,1,arr);
      else
        return -1;
    }
    delay(WAIT_KBC); // e.g. tickdelay()
  }
  return 0;
}

int(kbd_test_timed_scan)(uint8_t n) {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}
