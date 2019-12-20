#include "fs.h"

size_t ramdisk_read(void *buf, size_t offset, size_t len);
size_t ramdisk_write(const void *buf, size_t offset, size_t len);

size_t events_read(void *buf, size_t offset, size_t len);
size_t serial_write(const void *buf, size_t offset, size_t len);
size_t fb_write(const void *buf, size_t offset, size_t len);
size_t fbsync_write(const void *buf, size_t offset, size_t len);
size_t dispinfo_read(void *buf, size_t offset, size_t len);

typedef size_t (*ReadFn) (void *buf, size_t offset, size_t len);
typedef size_t (*WriteFn) (const void *buf, size_t offset, size_t len);

typedef struct {
  char *name;
  size_t size;
  size_t disk_offset;
  ReadFn read;
  WriteFn write;
  size_t open_offset;
} Finfo;

enum {FD_STDIN, FD_STDOUT, FD_STDERR, FD_FB};

size_t invalid_read(void *buf, size_t offset, size_t len) {
  panic("should not reach here");
  return 0;
}

size_t invalid_write(const void *buf, size_t offset, size_t len) {
  panic("should not reach here");
  return 0;
}

/* This is the information about all files in disk. */
static Finfo file_table[] __attribute__((used)) = {
  {"stdin", 0, 0, invalid_read, invalid_write},
  {"stdout", 0, 0, invalid_read, serial_write},
  {"stderr", 0, 0, invalid_read, serial_write},
  {"/dev/events", 0, 0, events_read, invalid_write},
  {"/dev/fb", 0, 0, invalid_read, fb_write},
  {"/dev/fbsync", 0, 0, invalid_read, fbsync_write},
  {"/proc/dispinfo", 128, 0, dispinfo_read, invalid_write},
  {"/dev/tty", 0, 0, invalid_read, serial_write},
#include "files.h"
};

#define NR_FILES (sizeof(file_table) / sizeof(file_table[0]))


int fs_open(const char *pathname) {
  int i = 0;
  for(; i < NR_FILES; i ++) {
    if(strcmp(pathname, file_table[i].name) == 0) {
      file_table[i].open_offset = 0;
//	  printf("I am opened || name: %s || disk_offset:%d || open_offset: %d || size: %d\n ", file_table[i].name, file_table[i].disk_offset, file_table[i].open_offset, file_table[i].size);
      return i;
    }
  }
  assert(i != NR_FILES);
  return -1;
}


size_t fs_write(int fd, const void *buf, size_t count) {
    size_t len = count;
	
	//if(file_table[fd].open_offset >= file_table[fd].size) {
//		printf("count:%d!!!!!!!!!!!!!!\n", count);
//		printf("open offset:%d!!!!!!!!!!!!!!\n", file_table[fd].open_offset);
//		printf("size:%d!!!!!!!!!!!!!!\n", file_table[fd].size);
//		printf("Write None!!!!!!!!!!!!!!\n");
	//    return 0;
	//}

    //if(file_table[fd].open_offset + count >= file_table[fd].size) {
    //  len = file_table[fd].size - file_table[fd].open_offset;
    //}
    //else {
    //  len = count;
    //}
	switch(fd) {
		case 0: case 3: case 6: 
			{
			    panic("Invalid write!!!!!!!!!");
			}
		case 1: case 2: case 4: case 5:
			{
			    size_t ret = file_table[fd].write(buf, file_table[fd].disk_offset + file_table[fd].open_offset, len);
//		        printf("ret:%d!!!!!!!!!!!!!!\n", ret);
                file_table[fd].open_offset += ret;
				return ret;
			}
		default:
			{
				if(count + file_table[fd].open_offset >= file_table[fd].size) {
				    len = file_table[fd].size - file_table[fd].open_offset;
				}
                size_t ret = ramdisk_write(buf, file_table[fd].disk_offset + file_table[fd].open_offset, len);
                file_table[fd].open_offset += ret;
                return ret;
			}
	}
}

size_t fs_read(int fd, void *buf, size_t count) {
    size_t len = count;
	
	//if(file_table[fd].open_offset >= file_table[fd].size) {
//		printf("Read None!!!!!!!!!!!!!!\n");
	//    return 0;
	//}
	
    //if(file_table[fd].open_offset + count >= file_table[fd].size) {
    //  len = file_table[fd].size - file_table[fd].open_offset;
    //}
    //else {
    //  len = count;
    //}
	switch(fd) {
		case 0: case 1: case 2: case 4: case 5:
			{
			    panic("Invalid read!!!!!!!!!");
			}
		case 3: case 6:
			{
			    size_t ret = file_table[fd].read(buf, file_table[fd].disk_offset + file_table[fd].open_offset, len);
//		        printf("ret:%d!!!!!!!!!!!!!!\n", ret);
                file_table[fd].open_offset += ret;
				return ret;
			}
		default:
			{
				if(count + file_table[fd].open_offset >= file_table[fd].size) {
				    len = file_table[fd].size - file_table[fd].open_offset;
				}
                size_t ret = ramdisk_read(buf, file_table[fd].disk_offset + file_table[fd].open_offset, len);
                file_table[fd].open_offset += ret;
                return ret;
			}
	}
}


 size_t fs_lseek(int fd, size_t offset, int whence) {
   switch(whence) {
     case SEEK_SET: {assert(offset <= file_table[fd].size); file_table[fd].open_offset = offset; return file_table[fd].open_offset;}
     case SEEK_CUR: {assert(file_table[fd].open_offset + offset <= file_table[fd].size); file_table[fd].open_offset += offset; return file_table[fd].open_offset;}
     case SEEK_END: {assert(offset <= 0); file_table[fd].open_offset = offset + file_table[fd].size; return file_table[fd].open_offset;}
     default: assert(0);
   }
    
}

int fs_close(int fd) {
     return 0;
}

//
void init_fs() {
  // TODO: initialize the size of /dev/fb
  file_table[4].size = screen_height() * screen_width() * 4; 
  
}
