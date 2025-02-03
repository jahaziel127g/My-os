#ifndef FS_H
#define FS_H

void fs_init();
int fs_create(const char* name);
int fs_write(int file_id, const char* content);
char* fs_read(int file_id);
void fs_list();

#endif
