/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * elftypes.h - Definitions for the different ELF types.
 *
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 *
 */

#ifndef __ELF_TYPES_H__
#define __ELF_TYPES_H__

#include "types.h"

#define ELF_MACHINE_MIPS 0x0008
#define ELF_SH_STRTAB ".shstrtab"

#define ELF_SECT_MAX_NAME 128

/* Structure defining a single elf section */
struct ElfSection
{
	/* Name index */
	u32 iName;
	/* Type of section */
	u32 iType;
	/* Section flags */
	u32 iFlags;
	/* Addr of section when loaded */
	u32 iAddr;
	/* Offset of the section in the elf */
	u32 iOffset;
	/* Size of the sections data */
	u32 iSize;
	/* Link info */
	u32 iLink;
	/* Info */
	u32 iInfo;
	/* Address alignment */
	u32 iAddralign;
	/* Entry size */
	u32 iEntsize;

	/* Aliased pointer to the data (in the original Elf) */
	u8 *pData;
	/* Name of the section */
	char szName[ELF_SECT_MAX_NAME];
	/* Index */
	int iIndex;
	/* Section Ref. Used for relocations */
	struct ElfSection *pRef;
	/* Indicates if this section is to be outputted */
	int blOutput;

    // !HACK Allocate this as if its a rel
    int fakeRel;
};

struct ElfProgram
{
	u32 iType;
	u32 iOffset;
	u32 iVaddr;
	u32 iPaddr;
	u32 iFilesz;
	u32 iMemsz;
	u32 iFlags;
	u32 iAlign;

	/* Aliased pointer to the data (in the original Elf)*/
	u8  *pData;
};

/* Structure to hold elf header data, in native format */
struct ElfHeader
{
	u32 iMagic;
	u32 iClass;
	u32 iData;
	u32 iIdver;
	u32 iType; 
	u32 iMachine; 
	u32 iVersion; 
	u32 iEntry; 
	u32 iPhoff; 
	u32 iShoff; 
	u32 iFlags; 
	u32 iEhsize;
	u32 iPhentsize; 
	u32 iPhnum; 
	u32 iShentsize; 
	u32 iShnum; 
	u32 iShstrndx; 
};

struct ElfReloc
{
	/* Pointer to the section name */
	const char* secname;
	/* Base address */
	u32 base;
	/* Type */
	u32 type;
	/* Symbol (if known) */
	u32 symbol;
	/* Offset into the file */
	u32 offset;
	/* New Address for the relocation (to do with what you will) */
	u32 addr;
};

/* Define ELF types */
typedef u32 Elf32_Addr; 
typedef u16 Elf32_Half;
typedef u32 Elf32_Off;
typedef s32 Elf32_Sword;
typedef u32 Elf32_Word;

#define ELF_MAGIC	0x464C457F

#define ELF_EXEC_TYPE 0x0002
#define ELF_PRX_TYPE  0xFFA0

#define SHT_NULL 0 
#define SHT_PROGBITS 1 // can be anything from code to other stuff
#define SHT_SYMTAB 2 // symbol tables contain a symbol table entry, local global symbols
#define SHT_STRTAB 3 // string table, at the end of an elf
#define SHT_RELA 4 
#define SHT_HASH 5 
#define SHT_DYNAMIC 6 
#define SHT_NOTE 7 
#define SHT_NOBITS 8 
#define SHT_REL 9 // relocation
#define SHT_SHLIB 10 
#define SHT_DYNSYM 11
#define SHT_MIPS_DWARF 0x7000001e
#define SHT_LOPROC 0x70000000 
#define SHT_HIPROC 0x7fffffff 
#define SHT_LOUSER 0x80000000 
#define SHT_HIUSER 0xffffffff

#define SHT_PRXRELOC (SHT_LOPROC | 0xA0)

// MIPS Reloc Entry Types
#define R_MIPS_NONE     0
#define R_MIPS_16       1
#define R_MIPS_32       2
#define R_MIPS_REL32    3
#define R_MIPS_26       4
#define R_MIPS_HI16     5
#define R_MIPS_LO16     6
#define R_MIPS_GPREL16  7
#define R_MIPS_LITERAL  8
#define R_MIPS_GOT16    9
#define R_MIPS_PC16     10
#define R_MIPS_CALL16   11
#define R_MIPS_GPREL32  12

#define SHF_WRITE 		1
#define SHF_ALLOC 		2
#define SHF_EXECINSTR 	4

#define PT_NULL 		0
#define PT_LOAD 		1
#define PT_DYNAMIC 		2
#define PT_INTERP 		3
#define PT_NOTE 		4
#define PT_SHLIB 		5
#define PT_PHDR 		6
#define PT_LOPROC 		0x70000000
#define PT_HIPROC 		0x7fffffff

// Elf header
#pragma pack(1)
typedef struct { 
	Elf32_Word e_magic;
	u8 e_class;
	u8 e_data;
	u8 e_idver;
	u8 e_pad[9];
	Elf32_Half e_type; // set to ELF_PRX_TYPE
	Elf32_Half e_machine; // 0x08 = MIPS
	Elf32_Word e_version; // elf is always version 1
	Elf32_Addr e_entry; // entry point to the executable, 0 if no entry point
	Elf32_Off e_phoff; // location of all program headers in the elf file, absolute address
	Elf32_Off e_shoff; // location of all section headers in the elf file, absolute address
	Elf32_Word e_flags; 
	Elf32_Half e_ehsize; // elf header size
	Elf32_Half e_phentsize; // size of each program header entry & total number of entries
	Elf32_Half e_phnum; // number of program headers
	Elf32_Half e_shentsize; // size of each section header
	Elf32_Half e_shnum; // number of section headers
	Elf32_Half e_shstrndx; // section header string table index
//} __attribute__((packed)) Elf32_Ehdr;
} Elf32_Ehdr;
#pragma pack()

// Section header
#pragma pack(1)
typedef struct { 
	Elf32_Word sh_name; 
	Elf32_Word sh_type; 
	Elf32_Word sh_flags; // 0x1=writable, 0x2=load into memory, 0x3=instructions
	Elf32_Addr sh_addr; // where it appears in memory
	Elf32_Off sh_offset; // offset from the elf file
	Elf32_Word sh_size; // how big it is inside of the elf file
	Elf32_Word sh_link; // Lk, we aren't linking to the symtab, why?
	Elf32_Word sh_info; // Inf 
	Elf32_Word sh_addralign; // Al
	Elf32_Word sh_entsize; // ES, how many entries inside of a section
//} __attribute__((packed)) Elf32_Shdr;
} Elf32_Shdr;
#pragma pack()

// Program header
// each segment has a program header, program headers initially were called segment headers
// program headers are defined after each other
// the location of the program headers is inside of the elf header, e_phoff
typedef struct { 
	Elf32_Word p_type; // 1 = PT_LOAD, will be loaded into memory
	Elf32_Off p_offset; // where in the elf file the segment is at
	Elf32_Addr p_vaddr; // where the first byte is in memory
	Elf32_Addr p_paddr; // physical address where the segment will be loaded
	Elf32_Word p_filesz; // size of the segment in the elf file
	Elf32_Word p_memsz; // if its larger than the size of the file the leftover bytes are intialized to 0
	Elf32_Word p_flags; // segment flags
	Elf32_Word p_align; // 16 byte boundary alignment
} Elf32_Phdr;

#define ELF32_R_SYM(i) ((i)>>8) 
#define ELF32_R_TYPE(i) ((u8)(i&0xFF))

typedef struct { 
	Elf32_Addr r_offset; 
	Elf32_Word r_info; 
} Elf32_Rel;

#pragma pack(1)
typedef struct { 
	Elf32_Word st_name; 
	Elf32_Addr st_value; 
	Elf32_Word st_size; 
	unsigned char st_info; 
	unsigned char st_other; 
	Elf32_Half st_shndx; 
//} __attribute__((packed)) Elf32_Sym;
} Elf32_Sym;
#pragma pack()

#define STB_LOCAL 0
#define STB_GLOBAL 1
#define STB_WEAK 2
#define STB_LOPROC 13
#define STB_HIPROC 15

#define ELF32_ST_BIND(i) ((i)>>4)
#define ELF32_ST_TYPE(i) ((i)&0xf)
#define ELF32_ST_INFO(b,t) (((b)<<4)+((t)&0xf))

#endif
