#include "ports.h"
#include "disk.h"

#define ATA_PRIMARY 0x1F0
#define ATA_PRIMARY_CTRL 0x3F6
#define SECTOR_SIZE 512

void ata_wait() {
    while (port_byte_in(ATA_PRIMARY_CTRL) & 0x80);
}

void ata_read_sector(int lba, char* buffer) {
    port_byte_out(ATA_PRIMARY + 6, 0xE0 | ((lba >> 24) & 0x0F));
    port_byte_out(ATA_PRIMARY + 2, 1);  // Sector count
    port_byte_out(ATA_PRIMARY + 3, (lba & 0xFF));
    port_byte_out(ATA_PRIMARY + 4, (lba >> 8) & 0xFF);
    port_byte_out(ATA_PRIMARY + 5, (lba >> 16) & 0xFF);
    port_byte_out(ATA_PRIMARY + 7, 0x20);  // Read command

    ata_wait();
    
    for (int i = 0; i < SECTOR_SIZE / 2; i++) {
        ((short*)buffer)[i] = port_word_in(ATA_PRIMARY);
    }
}

void ata_write_sector(int lba, const char* buffer) {
    port_byte_out(ATA_PRIMARY + 6, 0xE0 | ((lba >> 24) & 0x0F));
    port_byte_out(ATA_PRIMARY + 2, 1);
    port_byte_out(ATA_PRIMARY + 3, (lba & 0xFF));
    port_byte_out(ATA_PRIMARY + 4, (lba >> 8) & 0xFF);
    port_byte_out(ATA_PRIMARY + 5, (lba >> 16) & 0xFF);
    port_byte_out(ATA_PRIMARY + 7, 0x30);  // Write command

    ata_wait();

    for (int i = 0; i < SECTOR_SIZE / 2; i++) {
        port_word_out(ATA_PRIMARY, ((short*)buffer)[i]);
    }
}
