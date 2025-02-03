#ifndef MEMORY_H
#define MEMORY_H

typedef struct PageDirectory PageDirectory;

void setup_paging();
PageDirectory* create_page_directory();
void load_page_directory(PageDirectory* dir);

#endif
