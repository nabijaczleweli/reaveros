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

#include "path.h"
#include "console.h"
#include "efi.h"

namespace efi_loader
{
using EFI_DEVICE_PATH_TO_TEXT_NODE = char16_t * (*)(const EFI_DEVICE_PATH_PROTOCOL * device_node,
    bool display_only,
    bool allow_shortcuts);

using EFI_DEVICE_PATH_TO_TEXT_PATH = char16_t * (*)(const EFI_DEVICE_PATH_PROTOCOL * device_node,
    bool display_only,
    bool allow_shortcuts);

constexpr auto EFI_DEVICE_PATH_TO_TEXT_PROTOCOL_GUID =
    EFI_GUID{ 0x8b843e20, 0x8132, 0x4852, { 0x90, 0xcc, 0x55, 0x1a, 0x4e, 0x4a, 0x7f, 0x1c } };

struct EFI_DEVICE_PATH_TO_TEXT_PROTOCOL
{
    EFI_DEVICE_PATH_TO_TEXT_NODE ConvertDeviceNodeToText;
    EFI_DEVICE_PATH_TO_TEXT_PATH ConvertDevicePathToText;
};

void efi_loader::path::print() const
{
    console::print(_buffer);
}

namespace
{
    EFI_DEVICE_PATH_TO_TEXT_PROTOCOL * to_text_protocol = nullptr;

    auto to_text_init()
    {
        if (!to_text_protocol)
        {
            to_text_protocol = FIND_PROTOCOL(DEVICE_PATH_TO_TEXT);
            efi_loader::console::print(u" > DEVICE_PATH_TO_TEXT protocol found.\n\r");
        }

        return to_text_protocol;
    }
}

efi_loader::path::path(EFI_DEVICE_PATH_PROTOCOL * device_path)
    : _buffer{ to_text_init()->ConvertDevicePathToText(device_path, false, false) }
{
}

efi_loader::path::~path()
{
    // TODO: free the buffer
}
}
