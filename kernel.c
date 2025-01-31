#define VGA_ADDRESS 0xB8000
#define WHITE_ON_BLACK 0x0F

void clear_screen() {
    char* vga = (char*)VGA_ADDRESS;
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        vga[i] = ' ';
        vga[i + 1] = WHITE_ON_BLACK;
    }
}

void print(const char* message) {
    char* vga = (char*)VGA_ADDRESS;
    int index = 0;
    while (message[index]) {
        vga[index * 2] = message[index];
        vga[index * 2 + 1] = WHITE_ON_BLACK;
        index++;
    }
}

void kernel_main() {
    clear_screen();
    print("Hello, Kernel World!");
    while (1);  // Infinite loop to prevent exit
}
