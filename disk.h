#ifndef DISK_H
#define DISK_H

void ata_read_sector(int lba, char* buffer);
void ata_write_sector(int lba, const char* buffer);

#endif
