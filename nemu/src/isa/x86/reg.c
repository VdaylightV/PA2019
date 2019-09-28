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
	char ax[3] = "ax";
	char dx[3] = "dx";
	char cx[3] = "cx";
	char bx[3] = "bx";
	char bp[3] = "bp";
	char si[3] = "si";
	char di[3] = "di";
	char sp[3] = "sp";
	char al[3] = "ax";
	char dl[3] = "dx";
	char cl[3] = "cx";
	char bl[3] = "bx";
	char ah[3] = "ax";
	char dh[3] = "dx";
	char ch[3] = "cx";
	char bh[3] = "bx";
    char pc[3] = "pc";    
 
	if ( strcmp(&eax[0], s) == 0 ) {
	    return cpu.eax;
	}

	else if ( strcmp(&edx[0], s) == 0 ) {
	    return cpu.edx;
	}

	else if ( strcmp(&ecx[0], s) == 0 ) {
	    return cpu.ecx;
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

	else if ( strcmp(&ax[0], s) == 0 ) {
	    return cpu.gpr[0]._16;
	}

	else if ( strcmp(&dx[0], s) == 0 ) {
	    return cpu.gpr[2]._16;
	}

	else if ( strcmp(&cx[0], s) == 0 ) {
	    return cpu.gpr[1]._16;
	}
	
	else if ( strcmp(&bx[0], s) == 0 ) {
	    return cpu.gpr[3]._16;
	}
	
	else if ( strcmp(&sp[0], s) == 0 ) {
	    return cpu.gpr[4]._16;
	}

	else if ( strcmp(&bp[0], s) == 0 ) {
	    return cpu.gpr[5]._16;
	}

	else if ( strcmp(&si[0], s) == 0 ) {
	    return cpu.gpr[6]._16;
	}

	else if ( strcmp(&di[0], s) == 0 ) {
	    return cpu.gpr[7]._16;
	}

	else if ( strcmp(&al[0], s) == 0 ) {
	    return cpu.gpr[0]._8[0];
	}

	else if ( strcmp(&dl[0], s) == 0 ) {
	    return cpu.gpr[2]._8[0];
	}

	else if ( strcmp(&cl[0], s) == 0 ) {
	    return cpu.gpr[1]._8[0];
	}
	
	else if ( strcmp(&bl[0], s) == 0 ) {
	    return cpu.gpr[3]._8[0];
	}

	else if ( strcmp(&ah[0], s) == 0 ) {
	    return cpu.gpr[0]._8[1];
	}

	else if ( strcmp(&dh[0], s) == 0 ) {
	    return cpu.gpr[2]._8[1];
	}

	else if ( strcmp(&ch[0], s) == 0 ) {
	    return cpu.gpr[1]._8[1];
	}
	
	else if ( strcmp(&bh[0], s) == 0 ) {
	    return cpu.gpr[3]._8[1];
	}

	else if ( strcmp(&pc[0], s) == 0 ) {
	    return cpu.pc;
	}

	else {
	    assert(0);
	}
  return 0;
}
