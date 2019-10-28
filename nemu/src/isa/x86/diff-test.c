#include "nemu.h"
#include "monitor/diff-test.h"

bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {
  
  if(ref_r->edx != cpu.edx) {
      printf("EDX doesn't match!");
	  return false;
  }

  if(ref_r->eax != cpu.eax) {
      printf("EAX doesn't match!");
	  return false;
  }

  if(ref_r->ecx != cpu.ecx) {
      printf("ECX doesn't match!");
	  return false;
  }
  
  if(ref_r->ebx != cpu.ebx) {
      printf("EBX doesn't match!");
	  return false;
  }

  if(ref_r->esp != cpu.esp) {
      printf("ESP doesn't match!");
	  return false;
  }

  if(ref_r->ebp != cpu.ebp) {
      printf("EBP doesn't match!");
	  return false;
  }

  if(ref_r->esi != cpu.esi) {
      printf("ESI doesn't match!");
	  return false;
  }

  if(ref_r->edi != cpu.edi) {
      printf("EDI doesn't match!");
	  return false;
  }

  return true;
}

void isa_difftest_attach(void) {
}
