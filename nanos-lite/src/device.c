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
	//   char a = 't';
      //uint32_t time = uptime();
	  //strcat((char*)buf, &a);
	  // sprintf((char*)buf, "c %d", a);
	   /*
	   int i = 0;
	   _putc('\n');
	   while(((char*)(buf))[i] != '\0') {
	       _putc(((char*)(buf))[i]);
		   i ++;
	   }
	   */
	   return sprintf((char*)buf, "t %d\n", uptime());
	   int length = strlen(buf);
	   return length;
   } 

   else {
	   
	   char status = key & 0x8000 ? 'd': 'u';
	   sprintf((char*)buf, "k%c %s\n", status, keyname[key&0x7fff]);
	   
	   
       //char flag;
	   /*
	   const char *key_name = keyname[key & 0x7fff];
	   if ((key & 0x8000) == 0x8000) {
	       flag = 'd';
	   }
	   else 
	   {
	       flag = 'u';
	   }
	   */
	   //flag = '*';
	   //char str[3] = "##";
	   //strcat((char*)buf, str);
	   //sprintf((char*)buf, "k%c %s\n", flag, str);
	  /*
	   int i = 0;
	   _putc('\n');
	   while(((char*)(buf))[i] != '\0') {
	       _putc(((char*)(buf))[i]);
		   i ++;
	   }
	   */
	   int length = strlen(buf);
       return length;
	   
   }

}

static char dispinfo[128] __attribute__((used)) = {};

size_t dispinfo_read(void *buf, size_t offset, size_t len) {
	//strncpy((char*)buf, &(dispinfo[offset]), len);
  //return len;
  size_t count = (len + offset) > strlen(dispinfo) ? strlen(dispinfo) - offset : len;
  memcpy(buf, &(dispinfo[offset]), count);
  return strlen(&(dispinfo[offset]));
}

size_t fb_write(const void *buf, size_t offset, size_t len) {
//  int fd = fs_open("/dev/fb");
//  fs_lseek(fd, offset, SEEK_SET);
//  fs_write(fd, buf, len);
//void draw_rect(uint32_t *pixels, int x, int y, int w, int h);
    //uint32_t *fb = (uint32_t*) buf;
    int x = (offset / 4) % screen_width();
	int y = (offset / 4) / screen_width();
	for(int i = 0; i < len / 4; i ++) {
	   draw_rect(&((uint32_t *)buf)[i], x, y, 1, 1);
	   if(x==screen_width()) {
	       x = 0;
		   y++;
	   }
	   else{
	       x++;
	   }
	  // x = ((x % screen_width())++);
	  /*{
	  int temp = x % screen_width();
	  x = temp + 1;
	   if(x == 0 && i > 0) {
		   y ++;
	   }
	  }*/
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
  // described in the Navy-apps convention
  //int fd = fs_open("proc/dispinfo");
  //fs_read(fd, (void*)dispinfo,  128);
  sprintf(dispinfo, "WIDTH : %d\nHEIGHT:%d\n", screen_width(), screen_height());

}
