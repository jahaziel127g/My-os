..global _start
.extern kernel_main
.extern keyboard_handler

.section .multiboot
.align 4
.long 0x1BADB002
.long 0x00
.long -(0x1BADB002 + 0x00)

.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:

.section .text
_start:
    mov $stack_top, %esp
    call kernel_main  # Call the C kernel
    cli  # Disable interrupts (optional)
    hlt  # Halt the CPU
