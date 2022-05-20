#include <lcom/lcf.h>

#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  val &= 0x00FF;
  *lsb = (uint8_t) val;
  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  val = val >> 8;
  val &= 0x00FF;
  *msb = (uint8_t) val;
  return 0;
}

int (util_sys_inb)(int port, uint8_t *value) {
  uint32_t temp;
  if(sys_inb(port,&temp) != 0) {return 1;}
  temp &= 0x000000FF;
  *value = (uint8_t) temp;
  return 0;
}
