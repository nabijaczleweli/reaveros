/**
 * Reaver Project OS, Rose, Licence
 *
 * Copyright © 2016-2017 Michał "Griwes" Dominiak
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation is required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 **/

#include "config.h"
#include "cpu/cpuid.h"
#include "efi/console.h"
#include "efi/efi.h"
#include "efi/filesystem.h"
#include "efi/system_table.h"
#include "memory/map.h"
#include "video/mode.h"

extern "C" efi_loader::EFI_STATUS efi_main(efi_loader::EFI_HANDLE image_handle,
    efi_loader::EFI_SYSTEM_TABLE * system_table)
{
    if (system_table->header.signature != efi_loader::EFI_SYSTEM_TABLE_SIGNATURE)
    {
        // need a better way to handle this
        // probably also need a crc32 check, but fuck that right now
        *(volatile uint64_t *)nullptr = 0xdeadbeef;
        asm volatile("cli; hlt");
    }

    efi_loader::initialize(system_table, image_handle);
    efi_loader::console::initialize();

    efi_loader::console::print(u"ReaverOS UEFI bootloader\n\r");
    efi_loader::console::print(u"Version 0.0.1 alpha, codename \"Cotyledon\"\n\r");
    efi_loader::console::print(u"Copyright (C) 2016-2017 Reaver Project Team\n\n\r");

    efi_loader::console::print(u"[CPU] Checking CPU capabilities...\n\r");
    auto cpu_caps = efi_loader::detect_cpu();

    efi_loader::console::print(u"[EFI] Looking for own location...\n\r");
    auto source_directory = efi_loader::locate_source_directory(image_handle);

    /*efi_loader::console::print(u"[DSK] Loading configuration...\n\r");
    auto config = efi_loader::parse_config(efi_loader::load_file(source_directory / u"reaveros.conf"));

    efi_loader::console::print(u"[DSK] Loading kernel and initrd...\n\r");
    auto kernel = efi_loader::load_kernel(source_directory, config);
    auto initrd = efi_loader::load_initrd(source_directory, config);

    efi_loader::console::print(u"[GFX] Choosing video mode...\n\r");
    auto video_mode = efi_loader::choose_mode();

    efi_loader::console::print(u"[MEM] Getting memory map...\n\r");
    auto memory_map = efi_loader::get_memory_map();*/

    /*efi_loader::console::print(u"[MEM] Allocating memory regions...\n\r");
    efi_loader::console::print(u"[CPU] Preparing GDT and IDT...\n\r");
    efi_loader::console::print(u"[MEM] Preparing paging structures...\n\r");
    efi_loader::console::print(u"[GFX] Setting video mode...\n\r");
    efi_loader::console::print(u"[EFI] Bootloader done. Giving up EFI boot services and invoking the kernel.\n\r");*/

    *(volatile uint64_t *)nullptr = 0xdeadc0de;
    for (;;)
        ;
}
