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

#include "filesystem.h"
#include "console.h"
#include "efi.h"
#include "path.h"

namespace efi_loader
{
constexpr auto EFI_LOADED_IMAGE_PROTOCOL_GUID =
    EFI_GUID{ 0x5b1b31a1, 0x9562, 0x11d2, { 0x8e, 0x3f, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b } };

struct EFI_DEVICE_PATH_PROTOCOL;
using EFI_IMAGE_UNLOAD = void (*)();

struct EFI_LOADED_IMAGE_PROTOCOL
{
    std::uint32_t revision;
    EFI_HANDLE parent_handle;
    EFI_SYSTEM_TABLE * system_table;
    EFI_HANDLE device_handle;
    EFI_DEVICE_PATH_PROTOCOL * file_path;
    void * reserved;
    std::uint32_t load_options_size;
    void * load_options;
    void * image_base;
    std::uint64_t image_size;
    EFI_MEMORY_TYPE image_code_type;
    EFI_MEMORY_TYPE image_data_type;
    EFI_IMAGE_UNLOAD unload;
};

path locate_source_directory(EFI_HANDLE image_handle)
{
    auto loaded_image = FIND_PROTOCOL_FROM_HANDLE(image_handle, LOADED_IMAGE);
    console::print(u" > LOADED_IMAGE protocol found.\n\r");

    auto image_path = path{ loaded_image->file_path };
    console::print(u" > Loaded image path: ", image_path, u"\n\r");
    return image_path;
}
}
