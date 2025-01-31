.global _start
.extern kernel_main

.section .multiboot
.align 4
.long 0x1BADB002  # Magic Number
.long 0x00        # Flags
.long -(0x1BADB002 + 0x00)  # Checksum

.section .bss
.align 16
stack_bottom:
.skip 16384  # 16 KB Stack
stack_top:

.section .text
_start:
    # Set up stack
    mov $stack_top, %esp
    call kernel_main  # Jump to C kernel code
    hlt  # Halt the CPU if kernel_main returns
