#include "isr.h"

void (*interrupt_handlers[256])();

void register_interrupt_handler(int n, void (*handler)()) {
    interrupt_handlers[n] = handler;
}

void isr_handler(int irq) {
    if (interrupt_handlers[irq]) {
        interrupt_handlers[irq]();
    }
}
