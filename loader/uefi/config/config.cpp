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

#include "config.h"
#include "../efi/console.h"

namespace efi_loader
{
// std::string_view::substr throws on out-of-range; we can't do that here
auto substr(std::string_view str, std::size_t pos, std::size_t num = std::string_view::npos)
{
    str.remove_prefix(pos);

    if (num != std::string_view::npos)
    {
        str.remove_suffix(str.size() - num);
    }

    return str;
}

std::string_view config::operator[](std::string_view key) const
{
    std::string_view config = _config_file.get();

    for (auto pos = config.find('\n'); pos != std::string_view::npos; pos = config.find('\n'))
    {
        auto line = substr(config, 0, pos);
        config.remove_prefix(pos + 1);

        auto colon = line.find(':');
        if (colon == std::string_view::npos)
        {
            console::print(u"[ERR] Malformed config file detected!\n\r");
            asm volatile("cli; hlt");
        }

        // ...maybe, just maybe, I'll write a proper parser for this
        // but that day isn't today
        if (substr(line, 0, colon) == key)
        {
            return substr(line, line.find_first_not_of(' ', colon + 1));
        }
    }

    console::print(u"[ERR] Failed to find a value for the key `", key, u"` in the config file.\n\r");
    asm volatile("cli; hlt");
    __builtin_unreachable();
}
}
