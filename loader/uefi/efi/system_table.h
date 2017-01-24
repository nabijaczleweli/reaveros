/**
 * Reaver Project OS, Rose, Licence
 *
 * Copyright © 2017 Michał "Griwes" Dominiak
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

#pragma once

#include "types.h"

namespace efi_loader
{
struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL;
struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

struct EFI_RUNTIME_SERVICES;
struct EFI_BOOT_SERVICES;

struct EFI_CONFIGURATION_TABLE;

struct EFI_SYSTEM_TABLE
{
    EFI_TABLE_HEADER header;
    char16_t * firmware_vendor;
    std::uint32_t firmware_revision;
    EFI_HANDLE con_in_handle;
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL * con_in;
    EFI_HANDLE con_out_handle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL * con_out;
    EFI_HANDLE stderr_handle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL * stderr;

    EFI_RUNTIME_SERVICES * runtime_services;
    EFI_BOOT_SERVICES * boot_services;

    std::size_t number_of_table_entries;
    EFI_CONFIGURATION_TABLE * configuration_table;
};
}
