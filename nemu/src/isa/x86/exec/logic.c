#include "cpu/exec.h"
#include "cc.h"

make_EHelper(test) {
 rtl_and(&id_dest->val, &id_src->val, &id_dest->val);
 if (id_dest->val == 0) {
    cpu.eflags.ZF = 1;
 }
 else {
    cpu.eflags.ZF = 0;
 }
 // TODO();

  print_asm_template2(test);
}

make_EHelper(and) {
  if(id_src->width == 1 && id_dest->width == 4) {
      id_src->val = (uint32_t)id_src->val;
  }

  if(id_src->width == 1 && id_dest->width == 2) {
      id_src->val = (uint16_t)id_src->val;
  }
  rtl_and(&s0, &id_dest->val, &id_src->val);

  operand_write(id_dest, &s0);
  //TODO();

  print_asm_template2(and);
}

make_EHelper(xor) {
  rtl_xor(&s0, &id_dest->val, &id_src->val);
  
  operand_write(id_dest, &s0);
   //TODO();

  print_asm_template2(xor);
}

make_EHelper(or) {
  TODO();

  print_asm_template2(or);
}

make_EHelper(sar) {
  TODO();
  // unnecessary to update CF and OF in NEMU

  print_asm_template2(sar);
}

make_EHelper(shl) {
  TODO();
  // unnecessary to update CF and OF in NEMU

  print_asm_template2(shl);
}

make_EHelper(shr) {
  TODO();
  // unnecessary to update CF and OF in NEMU

  print_asm_template2(shr);
}

make_EHelper(setcc) {
  uint32_t cc = decinfo.opcode & 0xf;

  rtl_setcc(&s0, cc);
  operand_write(id_dest, &s0);

  print_asm("set%s %s", get_cc_name(cc), id_dest->str);
}

make_EHelper(not) {
  TODO();

  print_asm_template1(not);
}
