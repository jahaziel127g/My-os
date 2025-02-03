CC = gcc
AS = as
LD = ld
CFLAGS = -m32 -ffreestanding -nostdlib

all: kernel.bin

kernel.bin: boot.o kernel.o keyboard.o isr.o memory.o fs.o task.o disk.o
	$(LD) -m elf_i386 -T linker.ld -o kernel.bin $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(AS) $< -o $@

clean:
	rm -f *.o kernel.bin
