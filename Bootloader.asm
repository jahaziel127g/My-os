BITS 16            ; We start in real mode (16-bit)
ORG 0x7C00         ; BIOS loads bootloader here

start:
    cli            ; Disable interrupts
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00  ; Set up stack
    sti            ; Enable interrupts

    ; Print "Booting..." using BIOS
    mov si, boot_msg
    call print_string

    ; Load kernel (next sector) into memory at 0x1000
    mov ah, 0x02    ; BIOS read function
    mov al, 1       ; Read 1 sector
    mov ch, 0       ; Cylinder 0
    mov cl, 2       ; Sector 2 (bootloader is at sector 1)
    mov dh, 0       ; Head 0
    mov dl, 0x80    ; First hard drive
    mov bx, 0x1000  ; Load to 0x1000
    int 0x13        ; BIOS interrupt to read disk
    jc error        ; Jump if carry flag is set (error)

    ; Switch to 32-bit protected mode
    cli             ; Disable interrupts
    lgdt [gdt_descriptor]  ; Load GDT
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp 0x08:protected_mode  ; Far jump to new segment

error:
    hlt             ; Halt on error
    jmp error

; Print string subroutine
print_string:
    mov ah, 0x0E
.loop:
    lodsb           ; Load next character
    or al, al       ; If null, stop
    jz done
    int 0x10        ; Print character
    jmp .loop
done:
    ret

boot_msg db "Booting...", 0

; GDT for protected mode
gdt:
    dq 0x0000000000000000  ; Null descriptor
    dq 0x00CF9A000000FFFF  ; Code segment
    dq 0x00CF92000000FFFF  ; Data segment

gdt_descriptor:
    dw gdt_descriptor - gdt - 1
    dd gdt

[BITS 32]
protected_mode:
    mov ax, 0x10   ; Load data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov esp, 0x90000  ; Set up stack
    jmp 0x1000        ; Jump to kernel

times 510-($-$$) db 0  ; Fill up to 510 bytes
dw 0xAA55              ; Boot signature
