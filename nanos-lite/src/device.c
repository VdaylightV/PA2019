#include "common.h"
#include <amdev.h>

size_t serial_write(const void *buf, size_t offset, size_t len) {

  char* temp = (char*) buf;
  for(int i = 0; i < len; i ++) {
      _putc(temp[i]);
  }	
  return len;
}

#define NAME(key) \
  [_KEY_##key] = #key,

static const char *keyname[256] __attribute__((used)) = {
  [_KEY_NONE] = "NONE",
  _KEYS(NAME)
};

size_t events_read(void *buf, size_t offset, size_t len) {
   int key = read_key();
   if(key == _KEY_NONE) {
	   return sprintf((char*)buf, "t %d\n", uptime());
	   int length = strlen(buf);
	   return length;
   } 

   else {
	   
	   char status = key & 0x8000 ? 'd': 'u';
	   sprintf((char*)buf, "k%c %s\n", status, keyname[key&0x7fff]);
	   
	   int length = strlen(buf);
       return length;
	   
   }

}

static char dispinfo[128] __attribute__((used)) = {};

size_t dispinfo_read(void *buf, size_t offset, size_t len) {
	strncpy((char*)buf, &(dispinfo[offset]), len);
    return strlen(&(dispinfo[offset]));
	/*
  size_t count = (len + offset) > strlen(dispinfo) ? strlen(dispinfo) - offset : len;
  memcpy(buf, &(dispinfo[offset]), count);
  return strlen(&(dispinfo[offset]));
  */
}

size_t fb_write(const void *buf, size_t offset, size_t len) {

    uint32_t *fb = (uint32_t*) buf;
    int x = (offset / 4) % screen_width();
	int y = (offset / 4) / screen_width();
	for(int i = 0; i < len / 4; i ++) {
	   draw_rect(&fb[i], x, y, 1, 1);
	   
	  int temp = x % screen_width();
	  x = temp + 1;
	   if(x == 0 && i > 0) {
	 	   y ++;
	   }
	}
    return len;
}

size_t fbsync_write(const void *buf, size_t offset, size_t len) {
	draw_sync();
  return len;
}

void init_device() {
  Log("Initializing devices...");
  _ioe_init();

  // TODO: print the string to array `dispinfo` with the format
  sprintf(dispinfo, "WIDTH:%d\nHEIGHT:%d\n", screen_width(), screen_height());

}
