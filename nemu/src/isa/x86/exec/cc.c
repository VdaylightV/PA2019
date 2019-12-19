#include "rtl/rtl.h"

/* Condition Code */

void rtl_setcc(rtlreg_t* dest, uint8_t subcode) {
  bool invert = subcode & 0x1;
  enum {
    CC_O, CC_NO, CC_B,  CC_NB,
    CC_E, CC_NE, CC_BE, CC_NBE,
    CC_S, CC_NS, CC_P,  CC_NP,
    CC_L, CC_NL, CC_LE, CC_NLE,
  };
  //printf("HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHsubcode: %x\n",(subcode & 0xe));

  // TODO: Query EFLAGS to determine whether the condition code is satisfied.
  // dest <- ( cc is satisfied ? 1 : 0)
  switch (subcode & 0xe) {
    
    case CC_O: {if (cpu.eflags.OF == 1) (*dest) = 1; else (*dest) = 0; break; }
    case CC_B: {if (cpu.eflags.CF == 1) (*dest) = 1; else (*dest) = 0; break; }
    case CC_E: {*dest = cpu.eflags.ZF; break; }
    case CC_BE: {if (cpu.eflags.CF == 1 || cpu.eflags.ZF == 1) (*dest) = 1; else (*dest) = 0; break; }
    case CC_S: {if (cpu.eflags.SF == 1) (*dest) = 1; else (*dest) = 0; break; }
    case CC_L: {if (cpu.eflags.OF != cpu.eflags.SF && cpu.eflags.ZF == 0) (*dest) = 1; else (*dest) = 0; break; }
    case CC_LE: {if (cpu.eflags.ZF == 1 || cpu.eflags.SF != cpu.eflags.OF) (*dest) = 1; else (*dest) = 0; break; }
	  case CC_NE: {*dest = ~cpu.eflags.ZF; break; }
	  case CC_NL: {if (cpu.eflags.SF == cpu.eflags.OF || cpu.eflags.ZF == 1) (*dest) = 1; else (*dest) = 0; break; }
     
//      TODO();
    default: panic("should not reach here");
    case CC_P: panic("n86 does not have PF");
  }
//  printf("@@@@@____%d____@@@@@\n", *dest);

  if (invert) {
    rtl_xori(dest, dest, 0x1);
  }

//  printf("@@@@@____%d____@@@@@\n", *dest);
  assert(*dest == 0 || *dest == 1);
}
