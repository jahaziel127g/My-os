#include "task.h"
#include "memory.h"

#define MAX_TASKS 4
#define STACK_SIZE 1024

typedef struct {
    void (*entry)();
    char stack[STACK_SIZE];
    int active;
    PageDirectory* page_directory;
} Task;

static Task tasks[MAX_TASKS];
static int current_task = 0;

void task_init() {
    for (int i = 0; i < MAX_TASKS; i++) {
        tasks[i].active = 0;
    }
}

int task_create(void (*entry)(), int user_mode) {
    for (int i = 0; i < MAX_TASKS; i++) {
        if (!tasks[i].active) {
            tasks[i].entry = entry;
            tasks[i].active = 1;
            tasks[i].page_directory = create_page_directory();
            if (user_mode) {
                tasks[i].page_directory->physical_tables[1023] |= 0x4; // Mark as user mode
            }
            return i;
        }
    }
    return -1;
}

void task_switch() {
    for (int i = 0; i < MAX_TASKS; i++) {
        current_task = (current_task + 1) % MAX_TASKS;
        if (tasks[current_task].active) {
            load_page_directory(tasks[current_task].page_directory);
            tasks[current_task].entry();
            return;
        }
    }
}
