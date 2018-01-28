#!/bin/sh
mkdir -p mnt
sudo mount /dev/disk/by-label/MBED mnt
sudo cp BUILD/touch.bin mnt/touch.bin
sync
sudo umount mnt
