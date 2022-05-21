#include "snake.h"

uint8_t bit_timer;
uint8_t bit_kb;
uint8_t bit_m;

void playSnakeLoop() {
  bool end = true;
  extern int counter;
  int ipc_status;
  message msg;
  int r;
  uint32_t mask_timer = BIT(bit_timer);
  uint32_t mask_kb = BIT(bit_kb);
  uint32_t mask_mouse = BIT(bit_m);
  int time = 0;

  if(video_set_graphics(0x115) != 0) {
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



  while(end) { 
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
                  if(counter % 60 == 0) {
                    time++;
                  }
                }

                /* Keyboard Interrupts */
                if(msg.m_notify.interrupts & mask_kb) {
                  vg_draw_rectangle(20,20,50,50,0xff);
                }

                /* Mouse Interrupts */
                if (msg.m_notify.interrupts & mask_mouse) {
                  vg_draw_rectangle(40,40,50,50,0xff0);
                }

                if(time == 10) {
                  end = false;
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
