#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int hook_id = 2;
int counter = 0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  uint8_t st;
  uint16_t newFreq = TIMER_FREQ / freq;
  uint8_t lsb,msb;
  if(freq < 19 || freq > TIMER_FREQ) {
    return 1;
  }
  if(util_get_LSB(newFreq,&lsb) != 0) {return 1;}
  if(util_get_MSB(newFreq,&msb) != 0) {return 1;}
  timer_get_conf(timer,&st);
  st = st & (0x0F);
  st |= TIMER_LSB_MSB;
  switch (timer)
  {
  case 0:
    st |= TIMER_SEL0;
    break;
  
  case 1:
    st |= TIMER_SEL1;
    break;

  case 2:
    st |= TIMER_SEL2;
    break;
  
  default:
    break;
  }
  if(sys_outb(TIMER_CTRL,st) != 0) {return 1;}
  if(sys_outb(TIMER_0 + timer,lsb) != 0) {return 1;}
  if(sys_outb(TIMER_0 + timer,msb) != 0) {return 1;}
  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
  *bit_no = hook_id;
  if(sys_irqsetpolicy(TIMER0_IRQ,IRQ_REENABLE,&hook_id) != 0) {return 1;}
  return 0;
}

int (timer_unsubscribe_int)() {
  if(sys_irqrmpolicy(&hook_id) != 0) {return 1;}
  return 0;
}

void (timer_int_handler)() {
  counter++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  uint8_t readCMD;
  readCMD = (TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer));
  if(sys_outb(TIMER_CTRL,readCMD)!= 0) {return 1;}
  if(util_sys_inb(TIMER_0 + timer,st) != 0) {return 1;}
  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st,enum timer_status_field field) {
  union timer_status_field_val pr;
  switch (field)
  {
  case tsf_all:
    pr.byte = st;
    break;
  
  case tsf_base:
    st &= BIT(0);
    pr.bcd = false;
    if(st == 1) {
      pr.bcd = true;
    }
    break;

  case tsf_initial:
    st = st >> 4;
    st &= 0x03;
    if(st == 0x01) {
      pr.in_mode = LSB_only;
    }
    else if(st == 0x02) {
      pr.in_mode = MSB_only;
    }
    else if(st == 0x03) {
      pr.in_mode = MSB_after_LSB;
    }
    else {
      pr.in_mode = INVAL_val;
    }
    break;

  case tsf_mode:
    st = st >> 1;
    st &= 0x07;
    if(st == 0x00) {
      pr.count_mode = 0;
    }
    else if(st == 0x01) {
      pr.count_mode = 1;
    }
    else if(st == 0x02 || st == 0x06) {
      pr.count_mode = 2;
    }
    else if(st == 0x03 || st == 0x07) {
      pr.count_mode = 3;
    }
    else if(st == 0x04) {
      pr.count_mode = 4;
    }
    else if(st == 0x05) {
      pr.count_mode = 5;
    }
    break;
  
  default:
    break;
  }
  timer_print_config(timer,field,pr);
  return 0;
}
