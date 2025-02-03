#include "fs.h"
#include "disk.h"
#include "memory.h"
#include "string.h"

#define FS_MAGIC 0xDEADBEEF
#define MAX_FILES 16
#define FILE_NAME_LEN 32
#define FILE_CONTENT_SIZE 512
#define FS_SECTOR 10  // Store filesystem at sector 10

typedef struct {
    char name[FILE_NAME_LEN];
    char content[FILE_CONTENT_SIZE];
    int size;
    int used;
} File;

typedef struct {
    int magic;
    File files[MAX_FILES];
} FileSystem;

static FileSystem fs;

void fs_init() {
    ata_read_sector(FS_SECTOR, (char*)&fs);
    if (fs.magic != FS_MAGIC) {
        fs.magic = FS_MAGIC;
        for (int i = 0; i < MAX_FILES; i++) {
            fs.files[i].used = 0;
        }
        ata_write_sector(FS_SECTOR, (char*)&fs);
    }
}

int fs_create(const char* name) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (!fs.files[i].used) {
            strncpy(fs.files[i].name, name, FILE_NAME_LEN);
            fs.files[i].size = 0;
            fs.files[i].used = 1;
            ata_write_sector(FS_SECTOR, (char*)&fs);
            return i;
        }
    }
    return -1;
}

int fs_write(int file_id, const char* content) {
    if (file_id < 0 || file_id >= MAX_FILES || !fs.files[file_id].used) return -1;
    strncpy(fs.files[file_id].content, content, FILE_CONTENT_SIZE);
    fs.files[file_id].size = strlen(content);
    ata_write_sector(FS_SECTOR, (char*)&fs);
    return 0;
}

char* fs_read(int file_id) {
    if (file_id < 0 || file_id >= MAX_FILES || !fs.files[file_id].used) return NULL;
    return fs.files[file_id].content;
}

void fs_list() {
    print("Files:\n");
    for (int i = 0; i < MAX_FILES; i++) {
        if (fs.files[i].used) {
            print(fs.files[i].name);
            print("\n");
        }
    }
}
