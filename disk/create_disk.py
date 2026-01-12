#!/usr/bin/env python3
"""
Creates a FAT12 disk image containing config.htm for DeskHop.
This is a cross-platform alternative to create.sh that doesn't require sudo/mount.
"""

import struct
import os

SECTOR_SIZE = 512
TOTAL_SECTORS = 128
FAT_SECTORS = 1
ROOT_DIR_SECTORS = 4
DATA_START_SECTOR = 1 + FAT_SECTORS + ROOT_DIR_SECTORS  # Boot + FAT + Root Dir

def create_fat12_disk(config_htm_path, output_path):
    """Create a minimal FAT12 disk image with config.htm."""

    with open(config_htm_path, 'rb') as f:
        file_data = f.read()

    file_size = len(file_data)

    disk = bytearray(TOTAL_SECTORS * SECTOR_SIZE)

    boot_sector = bytearray(SECTOR_SIZE)
    boot_sector[0:3] = b'\xEB\x3C\x90'
    boot_sector[3:11] = b'DESKHOP '
    boot_sector[11:13] = struct.pack('<H', SECTOR_SIZE)
    boot_sector[13] = 1
    boot_sector[14:16] = struct.pack('<H', 1)
    boot_sector[16] = 1
    boot_sector[17:19] = struct.pack('<H', 64)
    boot_sector[19:21] = struct.pack('<H', TOTAL_SECTORS)
    boot_sector[21] = 0xF0
    boot_sector[22:24] = struct.pack('<H', FAT_SECTORS)
    boot_sector[24:26] = struct.pack('<H', 1)
    boot_sector[26:28] = struct.pack('<H', 1)
    boot_sector[28:32] = struct.pack('<I', 0)
    boot_sector[36] = 0x00
    boot_sector[38] = 0x29
    boot_sector[39:43] = struct.pack('<I', 0x00000000)
    boot_sector[43:54] = b'DESKHOP    '
    boot_sector[54:62] = b'FAT12   '
    boot_sector[510:512] = b'\x55\xAA'

    disk[0:SECTOR_SIZE] = boot_sector

    fat_offset = SECTOR_SIZE
    disk[fat_offset] = 0xF0
    disk[fat_offset + 1] = 0xFF
    disk[fat_offset + 2] = 0xFF

    clusters_needed = (file_size + SECTOR_SIZE - 1) // SECTOR_SIZE
    for i in range(clusters_needed):
        cluster = i + 2
        if i < clusters_needed - 1:
            next_cluster = cluster + 1
        else:
            next_cluster = 0xFFF

        fat_byte_offset = (cluster * 3) // 2
        if cluster % 2 == 0:
            disk[fat_offset + fat_byte_offset] = next_cluster & 0xFF
            disk[fat_offset + fat_byte_offset + 1] = (disk[fat_offset + fat_byte_offset + 1] & 0xF0) | ((next_cluster >> 8) & 0x0F)
        else:
            disk[fat_offset + fat_byte_offset] = (disk[fat_offset + fat_byte_offset] & 0x0F) | ((next_cluster & 0x0F) << 4)
            disk[fat_offset + fat_byte_offset + 1] = (next_cluster >> 4) & 0xFF

    root_dir_offset = SECTOR_SIZE * (1 + FAT_SECTORS)
    dir_entry = bytearray(32)
    dir_entry[0:8] = b'CONFIG  '
    dir_entry[8:11] = b'HTM'
    dir_entry[11] = 0x20
    dir_entry[22:24] = struct.pack('<H', 0)
    dir_entry[24:26] = struct.pack('<H', 0)
    dir_entry[26:28] = struct.pack('<H', 2)
    dir_entry[28:32] = struct.pack('<I', file_size)

    disk[root_dir_offset:root_dir_offset + 32] = dir_entry

    data_offset = DATA_START_SECTOR * SECTOR_SIZE
    disk[data_offset:data_offset + file_size] = file_data

    with open(output_path, 'wb') as f:
        f.write(disk)

    print(f"Created {output_path} ({len(disk)} bytes) with config.htm ({file_size} bytes)")

if __name__ == '__main__':
    script_dir = os.path.dirname(os.path.abspath(__file__))
    config_htm = os.path.join(script_dir, '..', 'webconfig', 'config.htm')
    output_img = os.path.join(script_dir, 'disk.img')

    create_fat12_disk(config_htm, output_img)
