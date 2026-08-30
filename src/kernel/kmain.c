#include <kernel/core/include/gdt.h>
#include <kernel/core/include/idt.h>
#include <kernel/core/include/irq.h>
#include <kernel/core/include/mmu.h>
#include <kernel/core/include/multiboot.h>
#include <kernel/drivers/video/video.h>
#include <kernel/utils/print.h>

const char *mbtype[] = {
	[1] = "AVAILABLE",
        [2] = "RESERVED",
        [3] = "ACPI_RECLAIMABLE",
        [4] = "NVS",
        [5] = "BADRAM"
};

static void kinit(struct multiboot_info *mbi, uint32 magic) 
{
	uint8 wrong_params = 0;

	/**
	 * Verificando se os parâmetros do GRUB
	 * vieram corretamente.
	 */
	if (magic != MULTIBOOT_BOOTLOADER_MAGIC) 
	{
		wrong_params |= (1 << 0);
	}

	if ((mbi->flags >> 6 & 1) == 0) 
	{
		wrong_params |= (1 << 1);
	}

	vidinit();

	if (wrong_params != 0) 
	{
		if (wrong_params & 1) 
		{
			printk("WRONG MAGIC NUMBER!\n");
		}

		if (wrong_params & 2) 
		{
			printk("INVALID MEMORY MAP!\n");
		}
	}

	/**
	 * Mostrando regiões da memória 
	 * disponíveis (ou não xD)
	 */
	for (uint32 i = 0; 
	     i < mbi->mmap_length; 
	     i += sizeof(struct multiboot_mmap_entry)) 
	{
		struct multiboot_mmap_entry *mme = 
			(struct multiboot_mmap_entry *)(mbi->mmap_addr + i);

		printk("Start Addr: %X | Length: %X\nSize: %X | Type: %s\n\n",
   	   	   mme->addr_low, mme->len_low + mme->len_high, mme->size, mbtype[mme->type]);

		if (mme->type == MULTIBOOT_MEMORY_AVAILABLE) 
		{
			/** Fazer algo */
		}
	}

	gdt_init();

	idt_init();
	irq_init();

	/**
	* IMPORTANTE!
	*      Aqui deve-se tratar a interrupção.
	*      Devido a algumas interrupções serem classificadas
	*      como 'fault', EIP não avança quando é salvo na stack,
	*      é apenas salvo o valor atual de EIP, e por isso,
	*      acaba-se travando o sistema, porque assim que a
	*      interrupção acaba, o kernel lê de novo a
	*      instrução que a causou, fazendo um loop infinito.
	*
	*      Tenho que achar uma forma de tratar essas interrupções,
	*      não posso apenas fingir que não existem.
	*/
	// asm volatile("int $0xa");

	printk("KERNEL START: %X\nKERNEL END: %X\n", &__kernel_pstart, &__kernel_pend);
}

void kmain
(struct multiboot_info *mbi, 
 uint32 		magic) 
{
	kinit(mbi, magic);

	viddump();
}
