#ifndef _LCOM_MOUSE_H_
#define _LCOM_MOUSE_H_

#include "i8042.h"
#include <lcom/lcf.h>


void (mouse_ih)();
int (mouse_subscribe_int)(uint8_t *bit_no);
int (mouse_unsubscribe_int)();
int (send_mouse_cmd)(uint8_t cmd);
int (utils_sys_inb)(int port, uint8_t *val);
void (mouse_set_packet)(struct packet *pacote);
int (check_ibf_full)();
int (mouse_disable_data_reporting)();
bool (check_output_buffer)();


#endif
