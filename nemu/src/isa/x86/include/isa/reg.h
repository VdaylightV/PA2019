#ifndef __X86_REG_H__
#define __X86_REG_H__

#include "common.h"

#define PC_START IMAGE_START

enum { R_EAX, R_ECX, R_EDX, R_EBX, R_ESP, R_EBP, R_ESI, R_EDI };
enum { R_AX, R_CX, R_DX, R_BX, R_SP, R_BP, R_SI, R_DI };
enum { R_AL, R_CL, R_DL, R_BL, R_AH, R_CH, R_DH, R_BH };

/* TODO: Re-organize the `CPU_state' structure to match the register
 * encoding scheme in i386 instruction format. For example, if we
 * access cpu.gpr[3]._16, we will get the `bx' register; if we access
 * cpu.gpr[1]._8[1], we will get the 'ch' register. Hint: Use `union'.
 * For more details about the register encoding scheme, see i386 manual.
 */

typedef struct {
    union{
        union {
	        uint32_t _32;
	        uint16_t _16;
		    uint8_t _8[2];
	        } gpr[8];

  /* Do NOT change the order of the GPRs' definitions. */

  /* In NEMU, rtlreg_t is exactly uint32_t. This makes RTL instructions
   * in PA2 able to directly access these registers.
   */
	  rtlreg_t eax, ecx, edx, ebx, esp, ebp, esi, edi;
      };
/*
  __attribute__ (rtlreg_t eax) = gpr[0]._32;
  __attribute__ (rtlreg_t ecx) = gpr[1]._32;
  __attribute__ (rtlreg_t edx) = gpr[2]._32;
  __attribute__ (rtlreg_t ebx) = gpr[3]._32;
  __attribute__ (rtlreg_t esp) = gpr[4]._32;
  __attribute__ (rtlreg_t ebp) = gpr[5]._32;
  __attribute__ (rtlreg_t esi) = gpr[6]._32;
  __attribute__ (rtlreg_t edi) = gpr[7]._32; 
*/
/*
 rtlreg_t eax = R_EAX;
 rtlreg_t ecx = R_ECX;
 rtlreg_t edx = R_EDX;
 rtlreg_t ebx = R_EBX;
 rtlreg_t esp = R_ESP;
 rtlreg_t ebp = R_EBP;
 rtlreg_t esi = R_ESI;
 rtlreg_t edi = R_EDI;
 */
  vaddr_t pc;

} CPU_state;

static inline int check_reg_index(int index) {
  assert(index >= 0 && index < 8);
  return index;
}

#define reg_l(index) (cpu.gpr[check_reg_index(index)]._32)
#define reg_w(index) (cpu.gpr[check_reg_index(index)]._16)
#define reg_b(index) (cpu.gpr[check_reg_index(index) & 0x3]._8[index >> 2])

static inline const char* reg_name(int index, int width) {
  extern const char* regsl[];
  extern const char* regsw[];
  extern const char* regsb[];
  assert(index >= 0 && index < 8);

  switch (width) {
    case 4: return regsl[index];
    case 1: return regsb[index];
    case 2: return regsw[index];
    default: assert(0);
  }
}

#endif
