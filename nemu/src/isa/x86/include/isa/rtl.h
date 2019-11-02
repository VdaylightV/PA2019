#ifndef __X86_RTL_H__
#define __X86_RTL_H__

#include "rtl/rtl.h"


/* RTL pseudo instructions */

static inline void rtl_lr(rtlreg_t* dest, int r, int width) {
  switch (width) {
    case 4: rtl_mv(dest, &reg_l(r)); return;
    case 1: rtl_host_lm(dest, &reg_b(r), 1); return;
    case 2: rtl_host_lm(dest, &reg_w(r), 2); return;
    default: assert(0);
  }
}

static inline void rtl_sr(int r, const rtlreg_t* src1, int width) {
  switch (width) {
    case 4: rtl_mv(&reg_l(r), src1); return;
    case 1: rtl_host_sm(&reg_b(r), src1, 1); return;
    case 2: rtl_host_sm(&reg_w(r), src1, 2); return;
    default: assert(0);
  }
}

static inline void rtl_push(const rtlreg_t* src1) {
  // esp <- esp - 4
  // M[esp] <- src1
/*  reg_l(R_ESP) -= 4;
  vaddr_write(reg_l(R_ESP), *src, 4);
*/
	cpu.esp -= 4;
	//printf("The value to be pushed: %x\n", *src1);
	//rtl_sext(&t1, src1, 4);
	rtl_sm(&cpu.esp, src1 , 4);
    
  // TODO();
}

static inline void rtl_pop(rtlreg_t* dest) {
  // dest <- M[esp]
  // esp <- esp + 4
  //rtl_mv(dest, &cpu.esp);
  /*printf("HHHHHHHHHHHHH___%x___HHHHHHHHHHHHHHH\n", cpu.esp);
  t1 = vaddr_read(cpu.esp, 4);
  printf("t1:%x!!!!!!!!!\n", t1);
  printf("HHHHHHHHHHHHH___%x___HHHHHHHHHHHHHHH\n", *dest);
  */
  rtl_lm(dest, &cpu.esp, 4);
  /*printf("HHHHHHHHHHHHH___%x___HHHHHHHHHHHHHHH\n", *dest);*/
  cpu.esp += 4;
  //TODO();
}

static inline void rtl_is_sub_overflow(rtlreg_t* dest,
    const rtlreg_t* res, const rtlreg_t* src1, const rtlreg_t* src2, int width) {
  //rtl_setrelop(RELOP_LTU, dest, res, src1
  // dest <- is_overflow(src1 - src2)
	switch(width) {
	    case 1: { if ((((*src1)>>7) && 0x1 == ((~(*src2)+1)>>7) && 0x1) && ((((*src1)>>7) && 0x1) != (((*res)>>7) && 0x1))) *dest = 1; else *dest = 0; break;}
	    case 2: { if ((((*src1)>>15) && 0x1 == ((~(*src2)+1)>>15) && 0x1) && ((((*src1)>>15) && 0x1) != (((*res)>>15) && 0x1))) *dest = 1; else *dest = 0; break;}
	    case 4: { if ((((*src1)>>31) && 0x1 == ((~(*src2)+1)>>31) && 0x1) && ((((*src1)>>31) && 0x1) != (((*res)>>31) && 0x1))) *dest = 1; else *dest = 0; break;}
	    default: assert(0);
	}
//	uint32_t c = 0x80000000;
//	printf("@@@@@@@@@@@@@@@@@@@@@       0x%x        @@@@@@@@@@@@@@@@@@@@@\n",(~c)+1 + c);
//	printf("@@@@@@@@@@@@@@@@@@@@@       0x%x        @@@@@@@@@@@@@@@@@@@@@\n",c - c);

  //TODO();
}

static inline void rtl_is_sub_carry(rtlreg_t* dest,
    const rtlreg_t* res, const rtlreg_t* src1) {
   // rtl_setrelop(RELOP_LTU, dest, src1, res);
	rtl_sub(&t0, src1, res);

	if(t0 == 0x80000000 && *src1 != 0x80000000)  {
		*dest = 0;	
	}

	else if ((*src1) < (*res)) {
	    *dest = 1;
	}
	else {

	    *dest = 0;
	}
  // dest <- is_carry(src1 - src2)
  //TODO();
}

static inline void rtl_is_add_overflow(rtlreg_t* dest,
    const rtlreg_t* res, const rtlreg_t* src1, const rtlreg_t* src2, int width) {
	switch(width) {
	    case 1: { if ((((*src1)>>7) && 0x1 == ((*src2)>>7) && 0x1) && ((((*src1)>>7) && 0x1) != (((*res)>>7) && 0x1))) *dest = 1; else *dest = 0; break;}
	    case 2: { if ((((*src1)>>15) && 0x1 == ((*src2)>>15) && 0x1) && ((((*src1)>>15) && 0x1) != (((*res)>>15) && 0x1))) *dest = 1; else *dest = 0; break;}
	    case 4: { if ((((*src1)>>31) && 0x1 == ((*src2)>>31) && 0x1) && ((((*src1)>>31) && 0x1) != (((*res)>>31) && 0x1))) *dest = 1; else *dest = 0; break;}
	    default: assert(0);
	}
  // dest <- is_overflow(src1 + src2)
  //TODO();
}

static inline void rtl_is_add_carry(rtlreg_t* dest,
    const rtlreg_t* res, const rtlreg_t* src1) {
	
	if (*res < *src1) {
	   *dest = 1;
	}

	else {
	   *dest = 0;
	}
	
  // dest <- is_carry(src1 + src2)
  //TODO();
}

#define connect(f) cpu.eflags.f

#define make_rtl_setget_eflags(f) \
  static inline void concat(rtl_set_, f) (const rtlreg_t* src) { \
    connect(f) =  *src; \
  } \
  static inline void concat(rtl_get_, f) (rtlreg_t* dest) { \
   *dest =  connect(f); \
  }

make_rtl_setget_eflags(CF)
make_rtl_setget_eflags(OF)
make_rtl_setget_eflags(ZF)
make_rtl_setget_eflags(SF)

static inline void rtl_update_ZF(const rtlreg_t* result, int width) {
  // eflags.ZF <- is_zero(result[width * 8 - 1 .. 0])
  switch(width) {
	  case 1: { if ( ((*result)&(0xff)) == 0 ) cpu.eflags.ZF = 1; else cpu.eflags.ZF = 0; break; }
	  case 2: { if ( ((*result)&(0xffff)) == 0 ) cpu.eflags.ZF = 1; else cpu.eflags.ZF = 0; break; }
	  case 4: { if ( ((*result)&(0xffffffff)) == 0 ) cpu.eflags.ZF = 1; else cpu.eflags.ZF = 0; break; }
      default: assert(0);
  }
  
  //TODO();
}

static inline void rtl_update_SF(const rtlreg_t* result, int width) {
  // eflags.SF <- is_sign(result[width * 8 - 1 .. 0])
  switch(width) {
	  case 1: { if ( (((*result) >> 7)&(0x1)) == 0 ) cpu.eflags.SF = 0; else cpu.eflags.SF = 1; break; }
	  case 2: { if ( (((*result) >> 15)&(0x1)) == 0 ) cpu.eflags.SF = 0; else cpu.eflags.SF = 1; break; }
	  case 4: { if ( (((*result) >> 31)&(0x1)) == 0 ) cpu.eflags.SF = 0; else cpu.eflags.SF = 1; break; }
      default: assert(0);
  }


  //TODO();
}

static inline void rtl_update_ZFSF(const rtlreg_t* result, int width) {
  rtl_update_ZF(result, width);
  rtl_update_SF(result, width);
}

#endif
