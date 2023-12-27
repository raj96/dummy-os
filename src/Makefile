CFLAGS=-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c -Iinclude
LDFLAGS=-T linker.ld -z noexecstack -melf_i386
ASM=nasm

.PHONY: all kernel-loader kernel-main kernel clean-dist

all: kernel

kernel-loader:
	$(ASM) -f elf32 kernel.s -o kernel.o
kernel-main:
	$(CC) $(CFLAGS) kmain.c -o kmain.o
	$(CC) $(CFLAGS) $$(find lib/drivers | grep -E "^.*\.c$$") -o driver.o
kernel: kernel-loader kernel-main
	$(LD) $(LDFLAGS) *.o -o kernel.elf
	$(MAKE) clean-dist
clean-dist:
	rm -f *.o
clean:
	$(MAKE) clean-dist
	rm -f kernel.elf
