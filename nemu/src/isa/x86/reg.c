#include "nemu.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

const char *regsl[] = {"eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi"};
const char *regsw[] = {"ax", "cx", "dx", "bx", "sp", "bp", "si", "di"};
const char *regsb[] = {"al", "cl", "dl", "bl", "ah", "ch", "dh", "bh"};

void reg_test() {
  srand(time(0));
  uint32_t sample[8];
  uint32_t pc_sample = rand();
  cpu.pc = pc_sample;

  int i;
  for (i = R_EAX; i <= R_EDI; i ++) {
    sample[i] = rand();
    reg_l(i) = sample[i];
    assert(reg_w(i) == (sample[i] & 0xffff));
  }

  assert(reg_b(R_AL) == (sample[R_EAX] & 0xff));
  assert(reg_b(R_AH) == ((sample[R_EAX] >> 8) & 0xff));
  assert(reg_b(R_BL) == (sample[R_EBX] & 0xff));
  assert(reg_b(R_BH) == ((sample[R_EBX] >> 8) & 0xff));
  assert(reg_b(R_CL) == (sample[R_ECX] & 0xff));
  assert(reg_b(R_CH) == ((sample[R_ECX] >> 8) & 0xff));
  assert(reg_b(R_DL) == (sample[R_EDX] & 0xff));
  assert(reg_b(R_DH) == ((sample[R_EDX] >> 8) & 0xff));

  assert(sample[R_EAX] == cpu.eax);
  assert(sample[R_ECX] == cpu.ecx);
  assert(sample[R_EDX] == cpu.edx);
  assert(sample[R_EBX] == cpu.ebx);
  assert(sample[R_ESP] == cpu.esp);
  assert(sample[R_EBP] == cpu.ebp);
  assert(sample[R_ESI] == cpu.esi);
  assert(sample[R_EDI] == cpu.edi);

  assert(pc_sample == cpu.pc);
}

void isa_reg_display() {
	printf("Register_id    Hexadecimal       Decimal\n");
	printf(("    eax:       0x%08x      %012dD\n"),cpu.eax,cpu.eax);
	printf(("    ecx:       0x%08x      %012dD\n"),cpu.ecx,cpu.ecx);
    printf(("    edx:       0x%08x      %012dD\n"),cpu.edx,cpu.edx);
	printf(("    ebx:       0x%08x      %012dD\n"),cpu.ebx,cpu.ebx);
    printf(("    esp:       0x%08x      %012dD\n"),cpu.esp,cpu.esp);
	printf(("    ebp:       0x%08x      %012dD\n"),cpu.ebp,cpu.ebp);
	printf(("    esi:       0x%08x      %012dD\n"),cpu.esi,cpu.esi);
	printf(("    edi:       0x%08x      %012dD\n"),cpu.edi,cpu.edi);
}

uint32_t isa_reg_str2val(const char *s, bool *success) {
	char eax[4] = "eax";
	char ecx[4] = "ecx";
	char edx[4] = "edx";
	char ebx[4] = "ebx";
	char esp[4] = "esp";
	char ebp[4] = "ebp";
	char esi[4] = "esi";
	char edi[4] = "edi";

	if ( strcmp(&eax[0], s) == 0 ) {
	    return cpu.eax;
	}

	else if ( strcmp(&ecx[0], s) == 0 ) {
	    return cpu.ecx;
	}

	else if ( strcmp(&edx[0], s) == 0 ) {
	    return cpu.edx;
	}
	
	else if ( strcmp(&ebx[0], s) == 0 ) {
	    return cpu.ebx;
	}
	
	else if ( strcmp(&esp[0], s) == 0 ) {
	    return cpu.esp;
	}

	else if ( strcmp(&ebp[0], s) == 0 ) {
	    return cpu.ebp;
	}

	else if ( strcmp(&esi[0], s) == 0 ) {
	    return cpu.esi;
	}

	else if ( strcmp(&edi[0], s) == 0 ) {
	    return cpu.edi;
	}

	else {
	    assert(0);
	}
  return 0;
}
