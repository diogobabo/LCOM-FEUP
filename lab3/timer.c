#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

static int hook_id = 2;
int counter = 0;
int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  
  if(freq > TIMER_FREQ || freq<19){ // frequencias invalidas
    return 1;
  }

  uint8_t st,ts;
  int error = timer_get_conf(timer,&st);
  if(error != 0) {
    printf("ERROR GETTING CONFIG!");
    return 1;
  }

  ts = st & 0x0F; // 4 primeiros bits q
  st = st | TIMER_LSB_MSB; // resetar os bits todos menos os 4 lsbs

  if(timer == 0){
    st = (st|TIMER_SEL0|TIMER_LSB_MSB);
  }
  else if(timer == 1){
    st = (st|TIMER_SEL1|TIMER_LSB_MSB);
  }
  else if(timer == 2){
    st = (st|TIMER_SEL2|TIMER_LSB_MSB);
  }

  uint16_t timer_freq = TIMER_FREQ / freq; // dividir a freq default pela rate HZ;
  
  uint8_t msb,lsb;
  util_get_LSB(timer_freq,&lsb);
  util_get_MSB(timer_freq,&msb);

  // envia a control word para o reg controlo e dps mete a frequencia nos timers
  return sys_outb(TIMER_CTRL,st)||sys_outb(TIMER_0+timer,lsb)||sys_outb(TIMER_0+timer,msb);
}

int (timer_subscribe_int)(uint8_t *bit_no) {
    /* To be implemented by the students */
    *bit_no = hook_id;
    sys_irqsetpolicy(0,IRQ_REENABLE,&hook_id);
    //printf("%s is not yet implemented!\n", __func__);

  return 0;
}

int (timer_unsubscribe_int)() {
  sys_irqrmpolicy(&hook_id);
  return 0;
}

void (timer_int_handler)() {
  counter++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  uint8_t readBCMD = (TIMER_RB_CMD | TIMER_RB_SEL(timer)|TIMER_RB_COUNT_);
  int sout,sin;
  sout = sys_outb(TIMER_CTRL,(u32_t)readBCMD);
  if(sout != 0) {
    printf("SYS OUTB NOT WORKING");
    return 1;
  }
  sin = util_sys_inb(TIMER_0+timer,st);
  if(sin != 0) {
    printf("SYS INB NOT WORKING");
    return 1;
  }
  return 0;
}
enum timer_init init_mode_func(uint8_t *st){ // funcao feita para saber o mode de inicialização

  *st = *st >> 4; // por os bits 4 e 5 no inicio
  *st &= 0x03; // fazer & com 00000011, assim então dá os bits 4 e 5

  if(*st == 0x01){
    return LSB_only;
  }
  else if(*st == 0x02){
    return MSB_only;
  }
  else if(*st == 0x03){
    return MSB_after_LSB;
  }
  else{
    return INVAL_val; // caso seja invalido
  }
}
uint8_t count_mode_func(uint8_t st){ // funcao feita para ajudar a saber o count mode,

  if(st == 0x06){
    return 2;
  }
  else if(st ==0x07 ){
    return 3;
  }
  else{
    return st;
  }

}
int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
  union timer_status_field_val test;

  if(field == tsf_all){
    test.byte = st;
  }
  else if(field == tsf_initial){

    test.in_mode = init_mode_func(&st);
  }
  else if(field == tsf_mode){
    st = st >> 1;
    st &= 0x07;
    test.count_mode = count_mode_func(st);
  }
  else if(field == tsf_base){
    test.bcd = ((st & BIT(0)) == 1);
  }

  int flag;
  flag = timer_print_config(timer,field,test);

  if(flag !=0){
    printf("timer_print_config failed \n");
    return 1;
  }

  //printf("%s is not yet implemented!\n", __func__);

  return 0;
}