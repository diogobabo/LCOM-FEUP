#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
    /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_unsubscribe_int)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

void (timer_int_handler)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  uint8_t readBCMD = (TIMER_RB_CMD | TIMER_RB_SEL(timer)|TIMER_RB_COUNT_);

   if(sys_outb(TIMER_CTRL,(u32_t)readBCMD) != 0) {
    printf("SYS OUTB NOT WORKING");
    return 1;
  }

 if(sys_inb(TIMER_0+timer,(u32_t *) &st) != 0) {
    printf("SYS INB NOT WORKING");
    return 1;
  }
  //printf("%s is not yet implemented!\n", __func__);
  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
  /* To be implemented by the students */
  union timer_status_field_val test;
  if(field == tsf_all){
    test.byte = st;
  }
  else if(field == tsf_initial){
    test.in_mode = (st & (BIT(5) | BIT(4)));
  }
  else if(field == tsf_mode){
    test.count_mode = (st & (BIT(1) | BIT(2) | BIT(3) ));
  }
  else if(field == tsf_base){
    test.bcd = (st & BIT(0));
  }
  timer_print_config(timer,field,test);

  printf("%s is not yet implemented!\n", __func__);

  return 1;
}
