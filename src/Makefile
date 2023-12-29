CFLAGS=-m32 -ggdb -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c -Iinclude -I/usr/lib/gcc/x86_64-linux-gnu/12/include
LDFLAGS=-T linker.ld -z noexecstack -melf_i386
ASM=nasm

.PHONY: all kernel-loader kernel-main kernel clean-dist

all: kernel

kernel-loader:
	$(ASM) -f elf32 kernel.s -o kernel.o

kernel-main:
	$(CC) $(CFLAGS) $$(find . | grep -E "^.*\.c$$")

kernel: kernel-loader kernel-main
	$(LD) $(LDFLAGS) *.o -o kernel.elf
	$(MAKE) clean-dist

clean-dist:
	rm -f *.o

clean:
	$(MAKE) clean-dist
	rm -f kernel.elf
