#!/bin/sh

if ! command -v "${mkfs_fat:=mkfs.fat}" >/dev/null
then
    if [ -x /sbin/mkfs.fat ]
    then
        mkfs_fat="/sbin/mkfs.fat"
    else
        echo 'Can'\''t find mkfs.fat; please install dosfstools, or provide via an environment variable $mkfs_fat.'
        exit 1
    fi
fi

set -e

make

fallocate -l 1474560 fat.img
"$mkfs_fat" fat.img
mmd -i fat.img EFI EFI/BOOT
mcopy -o -i fat.img BOOTX64.EFI ::/EFI/BOOT/BOOTX64.EFI
mcopy -o -i fat.img config/reaveros.conf ::/EFI/BOOT/reaveros.conf

qemu-system-x86_64 -no-kvm -bios ../../deps/ovmf/OVMF.fd -hda fat.img -monitor stdio -parallel file:/dev/stdout -cpu qemu64,+sse3,+sse4.1,+sse4.2 -m 2048 -smp 4 -vga std -M pc-i440fx-2.1

