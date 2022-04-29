#include "graphics.h"

int (video_set_VBEmode)(reg86_t *r86,uint16_t mode){
  memset(r86, 0, sizeof(*r86));
  r86->ah = 0x4F;
  r86->al = 0x02;
  r86->bx = mode | VBEBIT;
  r86->intno = 0x10;
  if( sys_int86(r86) != OK ) {
    printf("\tvg_exit(): sys_int86() failed \n");
    return 1;
  }
  return 0;
}
