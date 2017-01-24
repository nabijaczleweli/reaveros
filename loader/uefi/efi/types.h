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

#include <cstddef>
#include <cstdint>

namespace efi_loader
{
using EFI_HANDLE = void *;
using EFI_STATUS = std::size_t;

struct EFI_GUID
{
    std::uint32_t data1;
    std::uint16_t data2;
    std::uint16_t data3;
    std::uint8_t data4[8];
};

struct EFI_TABLE_HEADER
{
    std::uint64_t signature;
    std::uint32_t revision;
    std::uint32_t header_size;
    std::uint32_t crc32;
    std::uint32_t reserved;
};

enum class EFI_MEMORY_TYPE
{
    efi_reserved_memory_type,
    efi_loader_code,
    efi_loader_data,
    efi_boot_services_code,
    efi_boot_services_data,
    efi_runtime_services_code,
    efi_runtime_services_data,
    efi_conventional_memory,
    efi_unusable_memory,
    efi_acpi_reclaim_memory,
    efi_acpi_memory_nvs,
    efi_memory_mapped_io,
    efi_memory_mapped_io_port_space,
    efi_pal_code,
    efi_persistent_memory,
    efi_max_memory_type
};
}
