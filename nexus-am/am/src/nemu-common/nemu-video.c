#include <am.h>
#include <amdev.h>
#include <nemu.h>
#include <klib.h>

/*
static inline int min(int x, int y) {
  return (x < y) ? x : y;
}
*/

static uint32_t* const fb __attribute__((used)) = (uint32_t *)0x40000;
//static uint32_t fb[400 * 300] = {};

size_t __am_video_read(uintptr_t reg, void *buf, size_t size) {
  switch (reg) {
    case _DEVREG_VIDEO_INFO: {
      _DEV_VIDEO_INFO_t *info = (_DEV_VIDEO_INFO_t *)buf;
      uint32_t screen = inl(0x100);
      info->width = screen >> 16;;
      info->height = screen << 16 >> 16;
      return sizeof(_DEV_VIDEO_INFO_t);
    }
  }
  return 0;
}

size_t __am_video_write(uintptr_t reg, void *buf, size_t size) {
  switch (reg) {
    case _DEVREG_VIDEO_FBCTL: {
      _DEV_VIDEO_FBCTL_t *ctl = (_DEV_VIDEO_FBCTL_t *)buf;
//    else {
/*      int width = inw(SCREEN_ADDR + 2);
      uint32_t *fb = (uint32_t*)(uintptr_t)FB_ADDR;
      for(int i = 0; i < ctl->h; i ++) {
        for(int j = 0; j < ctl->w; j ++) {
          fb[(i + ctl->y)*width + j + ctl->x] = ctl->pixels[i*ctl->w + j];
        }
      }
*/
//    }
      int x = ctl->x, y = ctl->y, w = ctl->w, h = ctl->h;
      uint32_t *pixels = ctl->pixels;
      int cp_bytes = sizeof(uint32_t) * (w < 400-w ? w : 400-w);
      for (int j = 0; j < h && y + j < 300; j ++) {
        memcpy(&fb[(y + j) * 400 + x], pixels, cp_bytes);
        pixels += w;
      }


/*    int i;
    for( i = 0; i < ctl->h; i ++) {

      memcpy(fb+(ctl->y+i)*screen_width()+ctl->x, ctl->pixels+i*ctl->w,ctl->w*4);
    }
*/
    if (ctl->sync) {
       outl(0x104, 0);
      }
      return size;
    }
  }
  return 0;
}

void __am_vga_init() {   
  int i;
  int size = screen_width() *screen_height();
  uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
  for (i = 0; i < size; i ++) fb[i] = i;
  draw_sync();

}
