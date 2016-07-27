/**
 * Reaver Project OS, Rose, Licence
 *
 * Copyright © 2016 Michał "Griwes" Dominiak
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

#include <cstdint>

#include <efi.h>
#include <efiprot.h>

namespace efi_loader
{
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

#define PROTO_GUID(PROTO) PROTO ## _PROTOCOL
#define FIND_PROTOCOL_FROM_HANDLE(HANDLE, PROTO) \
    (reinterpret_cast<EFI_ ## PROTO *>(::efi_loader::open_protocol_by_guid(HANDLE, PROTO_GUID(PROTO))))
#define FIND_PROTOCOL(PROTO) \
    (reinterpret_cast<EFI_ ## PROTO *>(::efi_loader::open_protocol_by_guid(PROTO_GUID(PROTO))))

