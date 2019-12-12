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
      uint32_t time = uptime();
	   sprintf((char*)buf, "t %d\n", time);
	   int i = 0;
	   while(((char*)(buf))[i] != '\0') {
	       _putc(((char*)(buf))[i]);
		   i ++;
	   }
	   int length = strlen(buf);
	   // return sprintf((char*)buf, "t %d\n", uptime());
	   return length;
   } 

   else {
	   
/*	   char status = key & 0x8000 ? 'd': 'u';
	   return sprintf((char*)buf, "k%c %s\n", status, keyname[key&0x7fff]);
*/	   
	   
       char flag;
	   const char *key_name = keyname[key & 0x7fff];
	   if ((key & 0x8000) == 0x8000) {
	       flag = 'd';
	   }
	   else 
	   {
	       flag = 'u';
	   }
	   sprintf((char*)buf, "k%c %s\n", flag, key_name);
	   int i = 0;
	   while(((char*)(buf))[i] != '\0') {
	       _putc(((char*)(buf))[i]);
		   i ++;
	   }
	   int length = strlen(buf);
       return length;
	   
   }

}

static char dispinfo[128] __attribute__((used)) = {};

size_t dispinfo_read(void *buf, size_t offset, size_t len) {
  return 0;
}

size_t fb_write(const void *buf, size_t offset, size_t len) {
  return 0;
}

size_t fbsync_write(const void *buf, size_t offset, size_t len) {
  return 0;
}

void init_device() {
  Log("Initializing devices...");
  _ioe_init();

  // TODO: print the string to array `dispinfo` with the format
  // described in the Navy-apps convention
}
