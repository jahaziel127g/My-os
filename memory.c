#include "memory.h"
#include "isr.h"

#define PAGE_SIZE 4096
#define PAGE_ENTRIES 1024
#define KERNEL_MEM 0x100000  // 1 MB

typedef struct {
    unsigned int present  : 1;
    unsigned int rw       : 1;
    unsigned int user     : 1;
    unsigned int reserved : 9;
    unsigned int frame    : 20;
} PageEntry;

typedef struct {
    PageEntry entries[PAGE_ENTRIES];
} PageTable;

typedef struct {
    PageTable* tables[PAGE_ENTRIES];
    unsigned int physical_tables[PAGE_ENTRIES];
} PageDirectory;

PageDirectory* current_directory;

void load_page_directory(PageDirectory* dir) {
    asm volatile("mov %0, %%cr3" :: "r"(dir->physical_tables));
    unsigned int cr0;
    asm volatile("mov %%cr0, %0" : "=r"(cr0));
    cr0 |= 0x80000000;  // Enable paging
    asm volatile("mov %0, %%cr0" :: "r"(cr0));
}

PageDirectory* create_page_directory() {
    PageDirectory* dir = (PageDirectory*)KERNEL_MEM;
    for (int i = 0; i < PAGE_ENTRIES; i++) {
        dir->tables[i] = 0;
        dir->physical_tables[i] = 0;
    }

    return dir;
}

void setup_paging() {
    current_directory = create_page_directory();
    load_page_directory(current_directory);
}
