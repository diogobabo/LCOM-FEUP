#ifndef _PAUSE_H
#define _PAUSE_H

#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>
#include "kbcKeys.h"
#include <xpms/resume.xpm>
#include <xpms/exitPause.xpm>
#include "devices/graphics.h"


void PauseTimerHandler();
void PauseHandlerKBC(enum KEY k);
void drawPause(int opt);


#endif
