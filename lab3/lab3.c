#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>
#include "keyboard.h"
#include "i8042.h"

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
  bool twoBytes = false;
  int ipc_status;
  message msg;
  int r;
  uint8_t bit_no;
  uint8_t arr[2];
  if(kb_subscribe(&bit_no) != 0) {return 1;}
  uint32_t irq_set = BIT(bit_no);
  while( scode != ESCSCAN ) { /* You may want to use a different condition */
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
                    if(twoBytes) {
                      bool make = scode & BIT(7);/* cheking break code or make code*/
                      arr[1] = scode;
                      twoBytes = false; // se ja leu o 2 byte, então mete bool a false
                      kbd_print_scancode(!make,2,arr);
                    }
                    else {
                      if(scode != DEFSCAN) { // caso o 1 byte seja 0xe0, então é pq é um scode de 2 bytes
                        bool make = scode & BIT(7);/* cheking break code or make code*/
                        arr[0] = scode;
                        kbd_print_scancode(!make,1,arr); // aqui o size do array passa para 1
                      }
                     else {
                       twoBytes = true;
                       arr[0] = scode;
                     }
                    }
                  }
                }
                break;
              default:
                break; /* no other notifications expected: do nothi*/
            }
        }
  }
  if(kb_unsubscribe() != 0) {return 1;}

  return 0;
}

int(kbd_test_poll)() {
  extern int flag;
  bool twoBytes = false;
  extern uint8_t status;
  extern uint8_t scode;
  uint8_t arr[2];
  extern int counterK;
  while(scode != ESCSCAN) {
    kbc_ih();
    if (flag == 0){
      if(twoBytes) {
        bool make = scode & BIT(7);/* cheking break code or make code*/
        arr[1] = scode;
        twoBytes = false; // se ja leu o 2 byte, então mete bool a false
        kbd_print_scancode(!make,2,arr);
      }
      else {
        if(scode != DEFSCAN) { // caso o 1 byte seja 0xe0, então é pq é um scode de 2 bytes
          bool make = scode & BIT(7);/* cheking break code or make code*/
          arr[0] = scode;
          kbd_print_scancode(!make,1,arr); // aqui o size do array passa para 1
        }
        else {
          twoBytes = true;
          arr[0] = scode;
        }
      }
    }
    else{
      tickdelay(micros_to_ticks(WAIT_KBC));
      continue;
    } 
  }
  enable_interrupts();
  kbd_print_no_sysinb(counterK);
  return 0;
}

int(kbd_test_timed_scan)(uint8_t n) {
  extern int flag;
  extern uint8_t scode;
  extern int counter;
  int ipc_status;
  bool twoBytes = false;
  uint8_t saveTime = n;
  message msg;
  int r;
  uint8_t bit_no;
  uint8_t bit_no_timer;
  uint8_t arr[2];
  if(timer_subscribe_int(&bit_no_timer) != 0) {return 1;};
  if(kb_subscribe(&bit_no) != 0) {return 1;}
  uint32_t irq_set = BIT(bit_no); // mask kb
  uint32_t irq_set_timer = BIT(bit_no_timer); // mask timer
  while( scode != ESCSCAN && n > 0) { /* You may want to use a different condition */
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
                    if(twoBytes) {
                      bool make = scode & BIT(7);/* cheking break code or make code*/
                      arr[1] = scode;
                      twoBytes = false;
                      kbd_print_scancode(!make,2,arr);
                    }
                    else {
                      if(scode != DEFSCAN) { // caso o 1 byte seja 0xe0, então é pq é um scode de 2 bytes
                        bool make = scode & BIT(7);/* cheking break code or make code*/
                        arr[0] = scode;
                        kbd_print_scancode(!make,1,arr); // aqui o size do array passa para 1
                      }
                      else {
                        twoBytes = true;
                        arr[0] = scode;
                      }
                    }
                  }
                  counter = 0; // dar reset ao counter do timer
                  n = saveTime; // por o tempo no normal, porque houve scan code
                }

                if (msg.m_notify.interrupts & irq_set_timer) { /* subscri ... process it */
                  timer_int_handler();
                  if(counter % 60 == 0){
                    timer_print_elapsed_time();
                    n--;
                  }
                  
                }
                break;
              default:
                break; /* no other notifications expected: do nothi*/
            }
        }
  }
  if(timer_unsubscribe_int() != 0) {return 1;}
  if(kb_unsubscribe() != 0) {return 1;}

  return 0;
}
