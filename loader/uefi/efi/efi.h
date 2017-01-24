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

#pragma once

#include "types.h"

namespace efi_loader
{
constexpr auto EFI_SYSTEM_TABLE_SIGNATURE = 0x5453595320494249;
constexpr auto EFI_2_60_SYSTEM_TABLE_REVISION = ((2 << 16) | (60));
constexpr auto EFI_2_50_SYSTEM_TABLE_REVISION = ((2 << 16) | (50));
constexpr auto EFI_2_40_SYSTEM_TABLE_REVISION = ((2 << 16) | (40));
constexpr auto EFI_2_31_SYSTEM_TABLE_REVISION = ((2 << 16) | (31));
constexpr auto EFI_2_30_SYSTEM_TABLE_REVISION = ((2 << 16) | (30));
constexpr auto EFI_2_20_SYSTEM_TABLE_REVISION = ((2 << 16) | (20));
constexpr auto EFI_2_10_SYSTEM_TABLE_REVISION = ((2 << 16) | (10));
constexpr auto EFI_2_00_SYSTEM_TABLE_REVISION = ((2 << 16) | (00));
constexpr auto EFI_1_10_SYSTEM_TABLE_REVISION = ((1 << 16) | (10));
constexpr auto EFI_1_02_SYSTEM_TABLE_REVISION = ((1 << 16) | (02));

constexpr auto EFI_SYSTEM_TABLE_REVISION = EFI_2_60_SYSTEM_TABLE_REVISION;
constexpr auto EFI_SPECIFICATION_VERSION = EFI_SYSTEM_TABLE_REVISION;

constexpr auto EFI_SUCCESS = 0;

struct EFI_SYSTEM_TABLE;

extern EFI_SYSTEM_TABLE * system_table;
extern EFI_HANDLE image_handle;

inline void initialize(EFI_SYSTEM_TABLE * table, EFI_HANDLE handle)
{
    system_table = table;
    image_handle = handle;
}

void * open_protocol_by_guid(EFI_HANDLE, const EFI_GUID &);
void * open_protocol_by_guid(const EFI_GUID &);
}

#define PROTO_GUID(PROTO) EFI_##PROTO##_PROTOCOL_GUID
#define PROTOCOL(PROTO) EFI_##PROTO##_PROTOCOL
#define FIND_PROTOCOL_FROM_HANDLE(HANDLE, PROTO)                                                                       \
    (reinterpret_cast<PROTOCOL(PROTO) *>(::efi_loader::open_protocol_by_guid(HANDLE, PROTO_GUID(PROTO))))
#define FIND_PROTOCOL(PROTO)                                                                                           \
    (reinterpret_cast<PROTOCOL(PROTO) *>(::efi_loader::open_protocol_by_guid(PROTO_GUID(PROTO))))
