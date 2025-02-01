#include "task.h"
#include "memory.h"
#include "isr.h"
#include "ports.h"

#define MAX_TASKS 4
#define STACK_SIZE 1024
#define PIT_COMMAND 0x43
#define PIT_DATA 0x40
#define PIT_FREQUENCY 100  // 100 Hz

typedef struct {
    void (*entry)();
    char stack[STACK_SIZE];
    int active;
} Task;

static Task tasks[MAX_TASKS];
static int current_task = 0;

void switch_task() {
    for (int i = 0; i < MAX_TASKS; i++) {
        current_task = (current_task + 1) % MAX_TASKS;
        if (tasks[current_task].active) {
            tasks[current_task].entry();
            return;
        }
    }
}

void pit_callback() {
    switch_task();
}

void init_pit() {
    int divisor = 1193180 / PIT_FREQUENCY;
    port_byte_out(PIT_COMMAND, 0x36);
    port_byte_out(PIT_DATA, divisor & 0xFF);
    port_byte_out(PIT_DATA, (divisor >> 8) & 0xFF);
    
    register_interrupt_handler(32, pit_callback);  // IRQ0 = Timer
}

void task_init() {
    for (int i = 0; i < MAX_TASKS; i++) {
        tasks[i].active = 0;
    }
    init_pit();
}

int task_create(void (*entry)()) {
    for (int i = 0; i < MAX_TASKS; i++) {
        if (!tasks[i].active) {
            tasks[i].entry = entry;
            tasks[i].active = 1;
            return i;
        }
    }
    return -1;
}
