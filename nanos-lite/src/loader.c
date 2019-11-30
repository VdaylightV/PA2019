#include "proc.h"
#include <elf.h>
#include <stdio.h>

#ifdef __ISA_AM_NATIVE__
# define Elf_Ehdr Elf64_Ehdr
# define Elf_Phdr Elf64_Phdr
#else
# define Elf_Ehdr Elf32_Ehdr
# define Elf_Phdr Elf32_Phdr
#endif

size_t ramdisk_read(void *buf, size_t offset, size_t len);

static uintptr_t loader(PCB *pcb, const char *filename) {

/* 
  Elf_Ehdr elf_ehdr;
  Elf_Phdr elf_phdr;

  ramdisk_read(&elf_ehdr, 0, sizeof(elf_ehdr));
  
  for(uint16_t i = 0; i < elf_ehdr.e_phnum; i ++) {
	  printf("num:%d\n",elf_ehdr.e_phnum);
	  printf("i:%d\n",i);
      ramdisk_read(&elf_phdr, i * elf_ehdr.e_phentsize + elf_ehdr.e_phoff, elf_ehdr.e_phentsize);
	  if(elf_phdr.p_type == PT_LOAD) {
		  uint32_t* ptr = (uint32_t*)elf_phdr.p_vaddr;
		  size_t buf[elf_phdr.p_filesz];
	      ramdisk_read(buf, elf_phdr.p_offset, elf_phdr.p_filesz);

		  memcpy((uint32_t*)ptr, buf, elf_phdr.p_filesz);

		  printf("?????????????????????\n");
	      //ramdisk_read(ptr, elf_phdr.p_offset, elf_phdr.p_filesz);
		  if(elf_phdr.p_memsz > elf_phdr.p_filesz) {
		      memset((char*)(ptr + elf_phdr.p_filesz), 0, elf_phdr.p_memsz - elf_phdr.p_filesz);
		  }
	}
  }
*/
	Elf_Ehdr elf;
	ramdisk_read(&elf, 0, sizeof(elf));

	Elf_Phdr segment[elf.e_phnum];
	ramdisk_read(&segment, elf.e_phoff, elf.e_phentsize*elf.e_phnum);

	for(int i = 0; i < elf.e_phnum; i ++) {
	    if(segment[i].p_type == PT_LOAD) {
		    size_t content[segment[i].p_filesz];
			ramdisk_read(&content, segment[i].p_offset, segment[i].p_filesz);
			uint32_t *anch1 = (uint32_t*)segment[i].p_vaddr;

			memcpy(anch1, &content, segment[i].p_filesz);

		  if(segment[i].p_memsz > segment[i].p_filesz) {
			  char* anch2 = (char*)(segment[i].p_vaddr + segment[i].p_filesz);
		      memset(anch2, 0, segment[i].p_memsz - segment[i].p_filesz);

		  
		  }
			
		}
	}
/*          printf("Start of ELF_Header:0x%08x\n",&elf_ehdr);
          printf("Offset:0x%08x\n",elf_phdr.p_offset);
		  printf("Start:0x%08x\n", &elf_ehdr + (elf_phdr.p_offset)/52);*/
/*  printf("Start of ELF_Header:0x%08x\n",&elf_ehdr);
  printf("Filesz: 0x%08x\n", elf_phdr.p_filesz);
  printf("Phdr Size:%d\n",sizeof(elf_phdr));
  printf("Phdr Entry Number:%d\n",elf_ehdr.e_phnum);
  printf("Phdr First Entry Type:%d\n",elf_phdr.p_type);
  printf("Phdr First Entry Offset:0x%08x\n",elf_phdr.p_offset);
  printf("Phdr First Entry VirtAddr:0x%08x\n",elf_phdr.p_vaddr);*/
//		  printf("MemAddr: 0x%08x\n", ptr);
/*
  Elf_Ehdr elf_ehdr;
  Elf_Phdr elf_phdr;
  Elf_Phdr elf_phdr1;

  ramdisk_read(&elf_ehdr, 0, sizeof(elf_ehdr));
  ramdisk_read(&elf_phdr, sizeof(elf_ehdr), sizeof(elf_phdr));
  ramdisk_read(&elf_phdr1, sizeof(elf_ehdr) + sizeof(elf_phdr), sizeof(elf_phdr));
  printf("Phdr Entry Size:%d\n",elf_ehdr.e_phentsize);
  printf("Phdr Size:%d\n",sizeof(elf_phdr));
  printf("Phdr Entry Number:%d\n",elf_ehdr.e_phnum);
  printf("Phdr First Entry Type:%d\n",elf_phdr.p_type);
  printf("Phdr First Entry Offset:%d\n",elf_phdr.p_offset);
  printf("Phdr First Entry VirtAddr:%x\n",elf_phdr.p_vaddr);

  printf("Phdr Size:%d\n",sizeof(elf_phdr1));
  printf("Phdr First Entry Type:%d\n",elf_phdr1.p_type);
  printf("Phdr First Entry Offset:%d\n",elf_phdr1.p_offset);
  printf("Phdr First Entry VirtAddr:%x\n",elf_phdr1.p_vaddr);
*/
  //TODO();
//  char buf0[65535];
//  char* buf0_head = &buf0[0];
/*
  char buf1[65535];
  char* buf1_head = &buf1[0];

  char buf2[65535];
  char* buf2_head = &buf2[0];
*/
 //  ramdisk_read((char*)0x03001000, 0x001000, 0x03a43);
  /*memcpy((char*)0x03001000, buf0_head, 0x03a43);*/
 // memset((char*)(0x03001000+0x03a43), '0', 1);
 
/*  ramdisk_read(buf1_head, 0x005000, 0x01918);
  memcpy((char*)0x03005000, buf1_head, 0x01918);
  memset((char*)(0x03005000+0x01918), '0', 1);

  ramdisk_read(buf2_head, 0x007000, 0x00868);
  memcpy((char*)0x03008000, buf2_head, 0x008d8);
  memset((char*)(0x03008000+0x00868), '0', 0x00071);
*/
  return elf.e_entry;
}

void naive_uload(PCB *pcb, const char *filename) {
  uintptr_t entry = loader(pcb, filename);
  Log("Jump to entry = %x", entry);
  ((void(*)())entry) ();
}

void context_kload(PCB *pcb, void *entry) {
  _Area stack;
  stack.start = pcb->stack;
  stack.end = stack.start + sizeof(pcb->stack);

  pcb->cp = _kcontext(stack, entry, NULL);
}

void context_uload(PCB *pcb, const char *filename) {
  uintptr_t entry = loader(pcb, filename);

  _Area stack;
  stack.start = pcb->stack;
  stack.end = stack.start + sizeof(pcb->stack);

  pcb->cp = _ucontext(&pcb->as, stack, stack, (void *)entry, NULL);
}
