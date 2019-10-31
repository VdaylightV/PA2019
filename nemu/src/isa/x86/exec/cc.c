#include "rtl/rtl.h"

/* Condition Code */

void rtl_setcc(rtlreg_t* dest, uint8_t subcode) {
  bool invert = subcode & 0x1;
  enum {
    CC_O, CC_NO, CC_B,  CC_NB,
    CC_E, CC_NE, CC_BE, CC_NBE,
    CC_S, CC_NS, CC_P,  CC_NP,
    CC_L, CC_NL, CC_LE, CC_NLE,
	CC_GE
  };

  // TODO: Query EFLAGS to determine whether the condition code is satisfied.
  // dest <- ( cc is satisfied ? 1 : 0)
  switch (subcode & 0xe) {
    case CC_O:
    case CC_B:
    case CC_E: {*dest = cpu.eflags.ZF; break; }
    case CC_BE:
    case CC_S:
    case CC_L:
    case CC_LE:
	case CC_NE: {*dest = ~cpu.eflags.ZF; break; }
//	case CC_NL: {if ( cpu.eflags.CF == 1 ) (*dest) = 0; else (*dest) = 1; printf("@@@@@____%u____@@@@@\n", *dest); break; }
//	case CC_GE: {if ( cpu.eflags.CF == 1 ) (*dest) = 0; else (*dest) = 1; printf("@@@@@____%u____@@@@@\n", *dest); break; }
      TODO();
    default: panic("should not reach here");
    case CC_P: panic("n86 does not have PF");
  }
  printf("@@@@@____%u____@@@@@\n", *dest);

  if (invert) {
    rtl_xori(dest, dest, 0x1);
  }

  printf("@@@@@____%u____@@@@@\n", *dest);
  assert(*dest == 0 || *dest == 1);
}
