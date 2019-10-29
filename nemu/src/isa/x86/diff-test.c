#include "nemu.h"
#include "monitor/diff-test.h"

bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {
  
  if(ref_r->edx != cpu.edx) {
      printf("EDX doesn't match!!!!\n");
	  printf("The correct value of edx: %x!!!!\n", ref_r->edx);
	  printf("Correct EFLAGS: !!!!");
	  printf("ZF: %u\n",ref_r->eflags.ZF);
	  printf("CF: %u\n",ref_r->eflags.CF);
	  printf("SF: %u\n",ref_r->eflags.SF);
	  printf("OF: %u\n",ref_r->eflags.OF);
	  return false;
  }

  if(ref_r->eax != cpu.eax) {
      printf("EAX doesn't match!!!!\n");
	  printf("The correct value of eax: %x!!!!\n", ref_r->eax);
	  printf("Correct EFLAGS: !!!!");
	  printf("ZF: %u\n",ref_r->eflags.ZF);
	  printf("CF: %u\n",ref_r->eflags.CF);
	  printf("SF: %u\n",ref_r->eflags.SF);
	  printf("OF: %u\n",ref_r->eflags.OF);
	  printf("\n");
	  return false;
  }

  if(ref_r->ecx != cpu.ecx) {
      printf("ECX doesn't match!!!!\n");
	  printf("The correct value of ecx: %x!!!!\n", ref_r->ecx);
	  printf("Correct EFLAGS: !!!!");
	  printf("ZF: %u\n",ref_r->eflags.ZF);
	  printf("CF: %u\n",ref_r->eflags.CF);
	  printf("SF: %u\n",ref_r->eflags.SF);
	  printf("OF: %u\n",ref_r->eflags.OF);
	  printf("\n");
	  return false;
  }
  
  if(ref_r->ebx != cpu.ebx) {
      printf("EBX doesn't match!!!!\n");
	  printf("The correct value of ebx: %x!!!!\n", ref_r->ebx);
	  printf("Correct EFLAGS: !!!!");
	  printf("ZF: %u\n",ref_r->eflags.ZF);
	  printf("CF: %u\n",ref_r->eflags.CF);
	  printf("SF: %u\n",ref_r->eflags.SF);
	  printf("OF: %u\n",ref_r->eflags.OF);
	  printf("\n");
	  return false;
  }

  if(ref_r->esp != cpu.esp) {
      printf("ESP doesn't match!!!!\n");
	  printf("The correct value of esp: %x!!!!\n", ref_r->esp);
	  printf("Correct EFLAGS: !!!!");
	  printf("ZF: %u\n",ref_r->eflags.ZF);
	  printf("CF: %u\n",ref_r->eflags.CF);
	  printf("SF: %u\n",ref_r->eflags.SF);
	  printf("OF: %u\n",ref_r->eflags.OF);
	  printf("\n");
	  return false;
  }

  if(ref_r->ebp != cpu.ebp) {
      printf("EBP doesn't match!!!!\n");
	  printf("The correct value of ebp: %x!!!!\n", ref_r->ebp);
	  printf("Correct EFLAGS: !!!!");
	  printf("ZF: %u\n",ref_r->eflags.ZF);
	  printf("CF: %u\n",ref_r->eflags.CF);
	  printf("SF: %u\n",ref_r->eflags.SF);
	  printf("OF: %u\n",ref_r->eflags.OF);
	  printf("\n");
	  return false;
  }

  if(ref_r->esi != cpu.esi) {
      printf("ESI doesn't match!!!!\n");
	  printf("The correct value of esi: %x!!!!\n", ref_r->esi);
	  printf("Correct EFLAGS: !!!!");
	  printf("ZF: %u\n",ref_r->eflags.ZF);
	  printf("CF: %u\n",ref_r->eflags.CF);
	  printf("SF: %u\n",ref_r->eflags.SF);
	  printf("OF: %u\n",ref_r->eflags.OF);
	  printf("\n");
	  return false;
  }

  if(ref_r->edi != cpu.edi) {
      printf("EDI doesn't match!!!!\n");
	  printf("The correct value of edi: %x!!!!\n", ref_r->edi);
	  printf("Correct EFLAGS: !!!!");
	  printf("ZF: %u\n",ref_r->eflags.ZF);
	  printf("CF: %u\n",ref_r->eflags.CF);
	  printf("SF: %u\n",ref_r->eflags.SF);
	  printf("OF: %u\n",ref_r->eflags.OF);
	  printf("\n");
	  return false;
  }

  return true;
}

void isa_difftest_attach(void) {
}
