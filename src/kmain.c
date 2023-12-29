#include "multiboot.h"
#include "drivers/video/framebuffer.h"
#include "drivers/cursor.h"

int kmain(multiboot_info_t *mbi, uint32_t magic) {
	clrscr();
	FgColor = FB_LIGHT_BLUE;
	printf("============================================\n");
	printf("||\tDummyOS: By A Dummy, For A Dummy\t||\n");
	printf("============================================\n\n\n");

	FgColor = FB_LIGHT_GREEN;
	printf("Checking for multiboot magic...\n");
	if(magic != MULTIBOOT_BOOTLOADER_MAGIC) {
		printf("Magic is missing. Cannot proceed...");
		return 1;
	}

	printf("Getting memory information...\n");
	if(!((mbi->flags >> 6) & 0x1)) {
		printf("Memory map information unavailable. Cannot proceed...");
		return 2;
	}

	printf("\n=================\n");
	printf("Memory map info:\n");
	printf("=================\n");
	// printf("sizeof(uint8_t): %d\n", sizeof(uint8_t));
	// printf("sizeof(uint16_t): %d\n", sizeof(uint16_t));
	// printf("sizeof(uint32_t): %d\n", sizeof(uint32_t));
	// printf("sizeof(uint64_t): %d\n", sizeof(multiboot_uint64_t));

	// printf("Hextest: 0x%x\n", 0xFB12);

	uint8_t mod = mbi->mmap_length % sizeof(multiboot_memory_map_t);
	int32_t mmap_length = mbi->mmap_length;

	if(mod != 0) {
		mmap_length = mod * sizeof(multiboot_memory_map_t);
	}
	mmap_length -= sizeof(multiboot_memory_map_t);
	
	for(int32_t i = mmap_length; i >= 0; i-=sizeof(multiboot_memory_map_t)) {
		multiboot_memory_map_t *mbmm = (multiboot_memory_map_t *)(mbi->mmap_addr + i);

		if(mbmm->type == MULTIBOOT_MEMORY_AVAILABLE) {
			// kmem_init(mbmm->)
		} else if(mbmm->type == MULTIBOOT_MEMORY_BADRAM) {
			printf("Bad memory found at 0x%x\n", mbmm->addr_low);
		}

		printf("Start: 0x%x | Length: %d | Size: %d | Type: 0x%x\n", mbmm->addr_low, mbmm->len_low, mbmm->size, mbmm->type);
		printf("-------------------------------------------------------------\n");

	}
	
	// destroy_framebuffer();
    while (1) {}
}
