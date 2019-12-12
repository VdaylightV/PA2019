#include "fs.h"

size_t ramdisk_read(void *buf, size_t offset, size_t len);
size_t ramdisk_write(const void *buf, size_t offset, size_t len);

size_t events_read(void *buf, size_t offset, size_t len);
size_t serial_write(const void *buf, size_t offset, size_t len);

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
#include "files.h"
};

#define NR_FILES (sizeof(file_table) / sizeof(file_table[0]))

int fs_open(const char *pathname) {
  int i = 0;
  for(; i < NR_FILES; i ++) {
    if(strcmp(pathname, file_table[i].name) == 0) {
      file_table[i].open_offset = 0;
      return i;
    }
  }
  assert(i != NR_FILES);
  return -1;
}

size_t fs_write(int fd, const void *buf, size_t count) {
    size_t len;
    if(file_table[fd].open_offset + count >= file_table[fd].size) {
      len = file_table[fd].size - file_table[fd].open_offset;
    }
    else {
      len = count;
    }
  ramdisk_write(buf, file_table[fd].disk_offset + file_table[fd].open_offset, len);
  file_table[fd].open_offset += len;
  return len;
}

size_t fs_read(int fd, void *buf, size_t count) {
    size_t len;
    if(file_table[fd].open_offset + count >= file_table[fd].size) {
      len = file_table[fd].size - file_table[fd].open_offset;
    }
    else {
      len = count;
    }
    ramdisk_read(buf, file_table[fd].disk_offset + file_table[fd].open_offset, len);
    file_table[fd].open_offset += len;
    return len;
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


/*替换调试法
int fs_open(const char *pathname) {
    int i;
	for(i = 0; i < NR_FILES; i ++) {
	    if (strcmp(pathname, file_table[i].name) == 0) {
		    file_table[i].open_offset = 0;
			return i;
		}
	}
	panic("The file %s not found!", pathname);
}

int fs_close(int fd) {
  return 0;
}

int fs_read(int fd, void* buf, size_t len) {
    if(file_table[fd].read) {
	    size_t ret = file_table[fd].read(buf, file_table[fd].disk_offset + file_table[fd].open_offset, len);
		file_table[fd].open_offset += ret;
		return ret;
	}

//	else {
	  size_t count = file_table[fd].open_offset + len >= file_table[fd].size ? file_table[fd].size - file_table[fd].open_offset : len;
		ramdisk_read(buf, file_table[fd].open_offset + file_table[fd].disk_offset, count);
		file_table[fd].open_offset += count;
		return count;
//	}
}

int fs_write(int fd, void* buf, size_t len) {
	   if(file_table[fd].write) {
	    size_t ret = file_table[fd].write(buf, file_table[fd].disk_offset + file_table[fd].open_offset, len);
		file_table[fd].open_offset += ret;
		return ret;
	}

//	else {
    size_t count = file_table[fd].open_offset + len >= file_table[fd].size ? file_table[fd].size - file_table[fd].open_offset : len;
		ramdisk_write(buf, file_table[fd].open_offset + file_table[fd].disk_offset, count);
		file_table[fd].open_offset += count;
		return count;
//	}
}
__ssize_t fs_lseek(int fd, __ssize_t offset, int whence) {
  switch(whence) {
    case SEEK_SET:
      assert(offset <= file_table[fd].size);
      file_table[fd].open_offset = offset;
      break;

    case SEEK_CUR:
      assert(file_table[fd].open_offset + offset <= file_table[fd].size);
      file_table[fd].open_offset += offset;
      break;

    case SEEK_END:
      assert(offset <= 0);
      file_table[fd].open_offset = file_table[fd].size + offset;
      break;

    default:
      panic("Should not reach here");
  }

  return file_table[fd].open_offset;
  

}
*/
//
void init_fs() {
  // TODO: initialize the size of /dev/fb
}
