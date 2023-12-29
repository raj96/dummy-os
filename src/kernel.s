MAGIC_NUMBER equ 0x1BADB002
FLAGS equ 0x00000002		; Setting bit 1 to get mem_* and mmap_* information in multiboot
CHECKSUM equ -(MAGIC_NUMBER + FLAGS)
KERNEL_STACK_SIZE equ 32 * 1024

section .multiboot
align 4
	dd MAGIC_NUMBER
	dd FLAGS
	dd CHECKSUM

section .text
global _entry
global io_write
extern kmain

_entry:
	; Setting up the stack
	mov esp, kernel_stack_start
	; Passing multiboot and magic headers to kmain
	push eax	; 2nd parameter to kmain (multiboot header)
	push ebx	; 1st parameter to kmain (mbi)
	call kmain
	hlt

; io_write(address, data)
io_write:
	mov dx, [esp+4]	; Moving port address
	mov al, [esp+8]	; Moving data
	out dx, al
	ret

section .bss
align 4
resb KERNEL_STACK_SIZE
kernel_stack_start:
