#ifndef _MENU_H
#define _MENU_H

#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>
#include <xpms/playMenu.xpm>
#include "kbcKeys.h"
#include <xpms/exitMenu.xpm>
#include <xpms/mouseCursor.xpm>
#include "devices/graphics.h"

void MenuMouseHandler();
void MenuTimerHandler();
void MenuHandlerKBC(enum KEY k);
void drawMenu(int opt);
void drawCursor();
#endif
