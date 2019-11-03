#include "cpu/exec.h"
#include "cc.h"

make_EHelper(test) {
  s2 = 0;
/*  printf("src:\n");
  printf("simm:0x%x\n", id_src->simm);
  printf("val:0x%x\n", id_src->val);
  printf("width:0x%x\n", id_src->width);
  printf("dest:\n");
  printf("simm:0x%x\n", id_dest->simm);
  printf("val:0x%x\n", id_dest->val);
  printf("width:0x%x\n", id_dest->width);
*/  /*printf("HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n");*/
  //id_dest->width = decinfo.isa.is_operand_size_16 ? 2 : 4;
  //printf("HHHHHHHHHH:________the original s1:_0x%x__________:HHHHHHHHHHHHH\n",s1);
  //rtl_sext(&s1, &id_src->val, id_src->width);
  //printf("HHHHHHHHHH:________the src beforewidth:_%x__________:HHHHHHHHHHHHH\n",id_src->width);
  //printf("HHHHHHHHHH:________the src before extend:0x%x__________:HHHHHHHHHHHHH\n",id_src->val);
  //printf("HHHHHHHHHH:________the src after extend:_0x%x__________:HHHHHHHHHHHHH\n",s1);
  rtl_and(&s0, &id_dest->val, &id_src->val);
  //printf("HHHHHHHHHH:________the result after and:_%x__________:HHHHHHHHHHHHH\n",s0);
  //printf("HHHHHHHHHH:________the ZF before and:_%x__________:HHHHHHHHHHHHH\n",cpu.eflags.ZF);
  rtl_update_ZFSF(&s0, id_dest->width);
  //printf("HHHHHHHHHH:_________the ZF after and: %x__________:HHHHHHHHHHHHH\n",cpu.eflags.ZF);
  rtl_set_CF(&s2);
  rtl_set_OF(&s2);
 /*printf("HHHHHHHHHH:_________%u__________:HHHHHHHHHHHHH\n",s1);*/
 /*
 if (s1 == 0) {
    cpu.eflags.ZF = 1;
 }
 else {
    cpu.eflags.ZF = 0;
 }
 */
 // TODO();

  print_asm_template2(test);
}

make_EHelper(and) {
  
  //id_dest->width = decinfo.isa.is_operand_size_16 ? 2 : 4;
  //rtl_sext(&s1, &id_src->val, id_src->width);
  
  /*
  int32_t temp = (int32_t)id_src->val;
  temp = (temp << 24) >> 24;
  uint32_t rs = (uint32_t)temp;
  printf("HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH%u\n",rs);
  */
  s2 = 0;
  rtl_and(&s0, &id_dest->val, &id_src->val);
  rtl_update_ZFSF(&s0, id_dest->width);
  rtl_set_CF(&s2);
  rtl_set_OF(&s2);

  operand_write(id_dest, &s0);
  //TODO();

  print_asm_template2(and);
}

make_EHelper(xor) {
  s2 = 0;
  rtl_xor(&s0, &id_dest->val, &id_src->val);
  
  rtl_update_ZFSF(&s0, id_dest->width);
  rtl_set_CF(&s2);
  rtl_set_OF(&s2);
  operand_write(id_dest, &s0);
   //TODO();

  print_asm_template2(xor);
}

make_EHelper(or) {
	s2 = 0;
	rtl_or(&s0, &id_dest->val, &id_src->val);

  //TODO();

  rtl_update_ZFSF(&s0, id_dest->width);
  rtl_set_CF(&s2);
  rtl_set_OF(&s2);
  operand_write(id_dest, &s0);
  
  print_asm_template2(or);
}

make_EHelper(sar) {
  //TODO();
  rtl_sar(&s0, &id_dest->val, &id_src->val);
  rtl_update_ZFSF(&s0, id_dest->width);
  operand_write(id_dest, &s0);

  // unnecessary to update CF and OF in NEMU

  print_asm_template2(sar);
}

make_EHelper(shl) {
  //TODO();
  // unnecessary to update CF and OF in NEMU

  rtl_shl(&s0, &id_dest->val, &id_src->val);
  rtl_update_ZFSF(&s0, id_dest->width);
  operand_write(id_dest, &s0);
  print_asm_template2(shl);
}

make_EHelper(shr) {
  //TODO();
  // unnecessary to update CF and OF in NEMU

  rtl_shr(&s0, &id_dest->val, &id_src->val);
  rtl_update_ZFSF(&s0, id_dest->width);
  operand_write(id_dest, &s0);
  print_asm_template2(shr);
}

make_EHelper(setcc) {
  uint32_t cc = decinfo.opcode & 0xf;

  rtl_setcc(&s0, cc);
  operand_write(id_dest, &s0);

  print_asm("set%s %s", get_cc_name(cc), id_dest->str);
}

make_EHelper(not) {
  rtl_not(&s0, &id_dest->val);
  operand_write(id_dest, &s0);
  //TODO();

  print_asm_template1(not);
}
