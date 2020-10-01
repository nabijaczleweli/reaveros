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

#include <string_view>

#include "../efi/filesystem.h"

namespace efi_loader
{
struct config
{
public:
    config(file_buffer config_file) : _config_file{ std::move(config_file) }
    {
    }

    std::string_view operator[](std::string_view key) const;

private:
    file_buffer _config_file;
};
}
