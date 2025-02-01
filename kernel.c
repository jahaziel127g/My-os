#include "fs.h"
#include "task.h"

void task1() {
    print("Task 1 running...\n");
    while (1) task_switch();
}

void task2() {
    print("Task 2 running...\n");
    while (1) task_switch();
}

void shell() {
    char input[256];
    int index = 0;
    
    print("Simple Shell > ");
    
    while (1) {
        char key = read_key();
        if (key == '\n') {
            input[index] = 0;
            index = 0;
            print("\n");

            if (strcmp(input, "clear") == 0) {
                clear_screen();
            } else if (strcmp(input, "ls") == 0) {
                fs_list();
            } else if (strncmp(input, "touch ", 6) == 0) {
                fs_create(input + 6);
            } else if (strncmp(input, "echo ", 5) == 0) {
                fs_write(0, input + 5); // Writing to first file
            } else if (strcmp(input, "read") == 0) {
                print(fs_read(0));
                print("\n");
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

    fs_init();
    task_init();

    task_create(task1);
    task_create(task2);

    shell();
}
