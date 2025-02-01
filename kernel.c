#include "fs.h"
#include "task.h"
#include "disk.h"

void task1() {
    print("Task 1 running...\n");
    while (1);
}

void task2() {
    print("Task 2 running...\n");
    while (1);
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
                fs_write(0, input + 5);
            } else if (strcmp(input, "read") == 0) {
                print(fs_read(0));
                print("\n");
            } else if (strncmp(input, "diskread", 8) == 0) {
                char buffer[512];
                ata_read_sector(0, buffer);
                print(buffer);
                print("\n");
            } else if (strncmp(input, "diskwrite ", 10) == 0) {
                ata_write_sector(0, input + 10);
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
