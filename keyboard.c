#include "ports.h"
#include "isr.h"

#define KEYBOARD_DATA_PORT 0x60

void keyboard_callback() {
    unsigned char scancode = port_byte_in(KEYBOARD_DATA_PORT);
    // Convert scancode to ASCII and print it (simplified, no shift support)
    char key = (scancode == 0x1C) ? '\n' : 'X';  // 0x1C = Enter key
    print_char(key);
}

void init_keyboard() {
    register_interrupt_handler(35, keyboard_callback);  // IRQ1 = 33
}
