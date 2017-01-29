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
using EFI_DEVICE_PATH_TO_TEXT_NODE = EFIAPI char16_t * (*)(const EFI_DEVICE_PATH_PROTOCOL * device_node,
    bool display_only,
    bool allow_shortcuts);

using EFI_DEVICE_PATH_TO_TEXT_PATH = EFIAPI char16_t * (*)(const EFI_DEVICE_PATH_PROTOCOL * device_node,
    bool display_only,
    bool allow_shortcuts);

constexpr auto EFI_DEVICE_PATH_TO_TEXT_PROTOCOL_GUID =
    EFI_GUID{ 0x8b843e20, 0x8132, 0x4852, { 0x90, 0xcc, 0x55, 0x1a, 0x4e, 0x4a, 0x7f, 0x1c } };

struct EFI_DEVICE_PATH_TO_TEXT_PROTOCOL
{
    EFI_DEVICE_PATH_TO_TEXT_NODE convert_device_node_to_text;
    EFI_DEVICE_PATH_TO_TEXT_PATH convert_device_path_to_text;
};

using EFI_DEVICE_PATH_FROM_TEXT_NODE = EFIAPI EFI_DEVICE_PATH_PROTOCOL * (*)(const char16_t * text_device_node);

using EFI_DEVICE_PATH_FROM_TEXT_PATH = EFIAPI EFI_DEVICE_PATH_PROTOCOL * (*)(const char16_t * text_device_path);

constexpr auto EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL_GUID =
    EFI_GUID{ 0x5c99a21, 0xc70f, 0x4ad2, { 0x8a, 0x5f, 0x35, 0xdf, 0x33, 0x43, 0xf5, 0x1e } };

struct EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL
{
    EFI_DEVICE_PATH_FROM_TEXT_NODE convert_text_to_device_node;
    EFI_DEVICE_PATH_FROM_TEXT_PATH convert_text_to_device_path;
};

void path::print() const
{
    console::print(_buffer);
}

namespace
{
    EFI_DEVICE_PATH_TO_TEXT_PROTOCOL * to_text_protocol = nullptr;
    EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL * from_text_protocol = nullptr;

    auto to_text_init()
    {
        if (!to_text_protocol)
        {
            to_text_protocol = FIND_PROTOCOL(DEVICE_PATH_TO_TEXT);
            console::print(u" > DEVICE_PATH_TO_TEXT protocol found.\n\r");
        }

        return to_text_protocol;
    }

    auto from_text_init()
    {
        if (!from_text_protocol)
        {
            from_text_protocol = FIND_PROTOCOL(DEVICE_PATH_FROM_TEXT);
            console::print(u" > DEVICE_PATH_FROM_TEXT protocol found.\n\r");
        }

        return from_text_protocol;
    }
}

path::path(EFI_DEVICE_PATH_PROTOCOL * device_path)
    : _buffer{ to_text_init()->convert_device_path_to_text(device_path, false, false) }, _proto{ device_path }
{
}

path::~path()
{
    // TODO: free the buffer
}

path path::operator/(const char16_t * append) const
{
    char16_t buffer[16 * 1024];
    auto buffer_ptr = buffer;
    for (auto ptr = _buffer; *ptr; ++ptr)
    {
        *buffer_ptr++ = *ptr;
    }
    *buffer_ptr++ = u'\\';
    for (auto ptr = append; *ptr; ++ptr)
    {
        *buffer_ptr++ = *ptr;
    }
    *buffer_ptr = u'\0';

    auto proto = from_text_init()->convert_text_to_device_path(buffer);
    auto ret = path(proto);
    // free the proto
    return ret;
}
}
