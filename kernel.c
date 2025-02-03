#include "fs.h"
#include "task.h"
#include "disk.h"
#include "memory.h"

void user_process() {
    asm volatile(
        "mov $0x23, %ax\n"
        "mov %ax, %ds\n"
        "mov %ax, %es\n"
        "mov %ax, %fs\n"
        "mov %ax, %gs\n"
        "mov %esp, %eax\n"
        "pushl $0x23\n"
        "pushl %eax\n"
        "pushf\n"
        "pushl $0x1B\n"
        "pushl user_code\n"
        "iret\n"
        "user_code:\n"
        "mov $1, %ebx\n"
        "int $0x80\n"
    );
}

void kernel_main() {
    clear_screen();
    print("Welcome to the custom kernel!\n");

    setup_paging();
    fs_init();
    task_init();

    task_create(user_process, 1); // Create a user-mode process

    shell();
}
