#include "keyboard.h"
#include "memory.h"

void shell() {
    char input[256];
    int index = 0;
    
    print("Simple Shell > ");
    
    while (1) {
        char key = read_key();  // Blocking input
        if (key == '\n') {
            input[index] = 0;
            index = 0;
            print("\n");
            if (strcmp(input, "clear") == 0) {
                clear_screen();
            } else {
                print("Unknown command\n");
            }
            print("Simple Shell > ");
        } else {
            input[index++] = key;
            print_char(key);
        }
    }
}

void kernel_main() {
    clear_screen();
    print("Welcome to the custom kernel!\n");

    init_keyboard();
    
    shell();
}
