#include "graphics.h"
#include <math.h>

static char *video_mem;		/* Process (virtual) address to which VRAM is mapped */
static unsigned h_res;	        /* Horizontal resolution in pixels */
static unsigned v_res;	        /* Vertical resolution in pixels */
static unsigned int bytes_per_pixel; /* Number of VRAM bits per pixel */

int (video_set_graphics)(uint16_t mode){
  vbe_mode_info_t info;
  vbe_get_mode_info(mode,&info);

  h_res = info.XResolution;
  v_res = info.YResolution;

  struct minix_mem_range mr;
  unsigned int vram_base;  /* VRAM's physical addresss */
  unsigned int vram_size;  /* VRAM's size, but you can use the frame-buffer size, instead */
  int r;				    

  // igualar às valores da struct
  vram_base = info.PhysBasePtr;
  bytes_per_pixel = ceil(info.BitsPerPixel / 8);
  vram_size = h_res * v_res * bytes_per_pixel;


  mr.mr_base = (phys_bytes) vram_base;	
  mr.mr_limit = mr.mr_base + vram_size; 

  if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr))) {
   panic("sys_privctl (ADD_MEM) failed: %d\n", r);
  }

  /* Map memory */

  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);

  if(video_mem == MAP_FAILED) {
   panic("couldn't map video memory");
  }

  reg86_t r86;
  memset(&r86, 0, sizeof(r86));

  r86.ah = 0x4F;
  r86.al = 0x02;
  r86.bx = mode | VBEBIT;
  r86.intno = 0x10;

  if(sys_int86(&r86) != OK) {
    printf("\tvg_exit(): sys_int86() failed \n");
    return 1;
  }

  return 0;
}

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color) {
  uint8_t* pix;
  pix = (uint8_t* ) video_mem + (bytes_per_pixel * h_res * y + x * bytes_per_pixel);
  for(unsigned int i = 0; i < bytes_per_pixel; i++) { // em vez do loop fazer memcpy tb funciona
    uint8_t colorTemp = color & 0x000000FF; // 1 byte de cada vez
    *(i + pix) = colorTemp;
    color = color >> 8;
  }
  return 0;
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
  for(unsigned int i = 0; i < len; i++) {
    vg_draw_pixel(x + i,y,color);
  }
  return 0;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {

  for(unsigned int i = 0; i < height; i++) {
    vg_draw_hline(x,y + i,width,color);
  }
  return 0;
}
