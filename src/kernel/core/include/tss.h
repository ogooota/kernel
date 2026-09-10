#ifndef __TASK_STATE_SEGMENT_H
#define __TASK_STATE_SEGMENT_H

#include "kdefs.h"

struct tss 
{
	uint16 link;
	uint16 link_res;

	uint32 esp0;

	uint16 ss0;
	uint16 ss0_res;

	uint32 esp1;

	uint16 ss1;
	uint16 ss1_res;

	uint32 esp2;

	uint16 ss2;
	uint16 ss2_res;

	uint32 cr3;
	uint32 eip;
	uint32 eflags;
	uint32 eax;
	uint32 ecx;
	uint32 edx;
	uint32 ebx;
	uint32 esp;
	uint32 ebp;
	uint32 esi;
	uint32 edi;
	
	uint16 es;
	uint16 es_res;
	uint16 cs;
	uint16 cs_res;
	uint16 ss;
	uint16 ss_res;
	uint16 ds;
	uint16 ds_res;
	uint16 fs;
	uint16 fs_res;
	uint16 gs;
	uint16 gs_res;
	
	uint16 ldtr;
	uint16 ldtr_res;

	uint16 iobp_res;
	uint16 iobp;

	uint32 ssp;
} _packed;



#endif
