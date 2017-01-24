#!/usr/bin/env bash

set -e

make
mcopy -o -i fat.img BOOTX64.EFI ::/EFI/BOOT/BOOTX64.EFI
qemu-system-x86_64 -enable-kvm -bios ../../deps/ovmf/OVMF.fd -hda fat.img -monitor stdio -parallel file:/dev/stdout -cpu qemu64,+sse3,+sse4.1,+sse4.2,+x2apic -m 2048

