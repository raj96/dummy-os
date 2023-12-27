MAGIC_NUMBER equ 0x1BADB002
FLAGS equ 0x0
CHECKSUM equ -MAGIC_NUMBER
KERNEL_STACK_SIZE equ 16384

section .multiboot
align 4
	dd MAGIC_NUMBER
	dd FLAGS
	dd CHECKSUM

section .text
global _entry
extern kmain

_entry:
	; Setting up the stack
	mov esp, kernel_stack_start
	; Passing multiboot and magic headers to kmain
	push eax
	push ebx
	call kmain
	hlt

section .bss
align 4
resb KERNEL_STACK_SIZE
kernel_stack_start:
