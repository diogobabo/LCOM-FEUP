#include <lcom/lcf.h>
#include <keyboard.h>

uint8_t status = 0;
uint8_t scode = 0;
static int hook_id = 3;
int flag = 0;

int (util_sys_inb)(int port, uint8_t *value) {
  u32_t val = 0;

  int in;

  in = sys_inb(port,&val);

  *value = (uint8_t)val;
  return in;
}
 void (kbc_ih)(){
   
   int error1,error = util_sys_inb(STAT_REG,&status);
   error1 = util_sys_inb(OUT_BUF,scode);
   if(error != 0 || error1 != 0){
     printf("error reading status");
     return;
   }
   if((status & (ERROR_PARITY | ERROR_TIMEOUT)) != 0){
     printf("error in kdb");
     flag =1;
     return;
   }
 }
 int (keyboard_subscribe_int)(uint8_t *bit_no){
    *bit_no = hook_id;
    sys_irqsetpolicy(0,IRQ_REENABLE |IRQ_EXCLUSIVE,&hook_id);
  return 0;
  }
  int (keyboard_unsubscribe_int)(){
  sys_irqrmpolicy(&hook_id);
  return 0;
  }
