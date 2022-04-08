#ifndef _LCOM_KBD_H_
#define _LCOM_KBD_H_

#include <lcom/lcf.h>

#define STAT_REG 0x64
#define OUT_BUF 0x60
#define CMD1 0x20
#define CMD2 0X60
#define INT  BIT(0)
#define IRQ_KB 1
#define ERROR_PARITY  BIT(7)
#define ERROR_TIMEOUT  BIT(6)
#define WAIT_KBC    20000
#define KBC_OBF  BIT(0)
#define KBC_AUX  BIT(5)



#endif
