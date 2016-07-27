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
#include "filesystem.h"
#include "console.h"

using EFI_DEVICE_PATH_TO_TEXT_NODE = CHAR16 * (EFIAPI *)(
    IN CONST EFI_DEVICE_PATH * DeviceNode,
    IN BOOLEAN DisplayOnly,
    IN BOOLEAN AllowShortcuts
);

using EFI_DEVICE_PATH_TO_TEXT_PATH = CHAR16 * (EFIAPI *)(
    IN CONST EFI_DEVICE_PATH * DeviceNode,
    IN BOOLEAN DisplayOnly,
    IN BOOLEAN AllowShortcuts
);

struct EFI_DEVICE_PATH_TO_TEXT
{
    EFI_DEVICE_PATH_TO_TEXT_NODE ConvertDeviceNodeToText;
    EFI_DEVICE_PATH_TO_TEXT_PATH ConvertDevicePathToText;
};

#define DEVICE_PATH_TO_TEXT_PROTOCOL \
    { 0x8b843e20, 0x8132, 0x4852, { 0x90, 0xcc, 0x55, 0x1a, 0x4e, 0x4a, 0x7f, 0x1c } }

efi_loader::path efi_loader::locate_source_directory(EFI_HANDLE image_handle)
{
    auto loaded_image = FIND_PROTOCOL_FROM_HANDLE(image_handle, LOADED_IMAGE);
    console::print(u" > LOADED_IMAGE protocol found.\n\r");

    auto to_text = FIND_PROTOCOL(DEVICE_PATH_TO_TEXT);
    console::print(u" > DEVICE_PATH_TO_TEXT protocol found.\n\r");

    auto path = to_text->ConvertDevicePathToText(loaded_image->FilePath, false, false);
    console::print(u" > Loaded image path: ", path, u"\n\r");

    return {};
}

