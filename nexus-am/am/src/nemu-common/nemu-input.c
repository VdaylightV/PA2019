#include <am.h>
#include <amdev.h>
#include <nemu.h>

#define KEYDOWN_MASK 0x8000

size_t __am_input_read(uintptr_t reg, void *buf, size_t size) {
  switch (reg) {
    case _DEVREG_INPUT_KBD: {
      _DEV_INPUT_KBD_t *kbd = (_DEV_INPUT_KBD_t *)buf;
      kbd->keycode = _KEY_NONE;
      int input = inl(0x60);
      if(input != _KEY_NONE) {
          kbd->keycode = input;
          kbd->keydown = !(kbd->keydown);
      }
      return sizeof(_DEV_INPUT_KBD_t);
    }
  }
  return 0;
}
