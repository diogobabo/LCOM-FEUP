#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>

void (kbc_ih)();

int (util_sys_inb)(int port, uint8_t *value);

int (keyboard_subscribe_int)(uint8_t *bit_no);

int (keyboard_unsubscribe_int)();

void (kbc_ph)();

void(enable_interrupts)();

#endif
