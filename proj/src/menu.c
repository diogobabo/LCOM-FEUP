#include <stdbool.h>
#include "menu.h"
#include "graphics.h"


int drawMenu() {
    uint8_t *map;
    uint8_t *map2;
    xpm_image_t img;
    xpm_image_t img2;
    map = xpm_load(menu_xpm,XPM_8_8_8_8,&img);
    map2 = xpm_load(menu2_xpm,XPM_8_8_8_8,&img2);

    draw_pix_map(0,0,map,img);
}

int selectMenu(uint8_t scode) {
    bool play;

    if(scode == ARROW_UP) {
        play = true;
        draw_pix_map(0,0,map,img);
    }

    if (scode == ARROW_DOWN) {
        play = false;
        draw_pix_map(0,0,map2,img2);
    }

    if (scode == ENTER) {
        if(play) {
            // enter the game
        }
        else {
            // end the application
        }
    }

}