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

#include "efi.h"
#include "console.h"

EFI_SYSTEM_TABLE * efi_loader::system_table = nullptr;
EFI_HANDLE efi_loader::image_handle = {};

void * efi_loader::open_protocol_by_guid(const EFI_GUID & guid)
{
    void * ret;
    auto status = system_table->BootServices->LocateProtocol(
        const_cast<EFI_GUID *>(&guid),
        NULL,
        &ret
    );

    if (status != EFI_SUCCESS)
    {
        console::print(u" >> Failed to open protocol. [TODO: print the guid here]\n\r");
        return nullptr;
    }

    return ret;
}

void * efi_loader::open_protocol_by_guid(EFI_HANDLE handle, const EFI_GUID & guid)
{
    void * ret;
    auto status = system_table->BootServices->OpenProtocol(
        handle,
        const_cast<EFI_GUID *>(&guid),
        &ret,
        image_handle,
        nullptr,
        EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL
    );

    if (status != EFI_SUCCESS)
    {
        console::print(u" >> Failed to open protocol. [TODO: print the guid here]\n\r");
        return nullptr;
    }

    return ret;
}

