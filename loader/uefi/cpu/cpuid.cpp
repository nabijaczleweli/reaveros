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

#include <cstdint>

#include "../efi/console.h"
#include "cpuid.h"

#define cpuid(id, a, b, c, d) asm volatile("cpuid" : "=a"(a), "=b"(b), "=c"(c), "=d"(d) : "a"(id));

namespace efi_loader
{
cpu_capabilities detect_intel()
{
    cpu_capabilities caps;
    console::print(u" > Intel CPU detected.\n\r");
    caps.manufacturer = cpu_manufacturer::intel;
    return caps;
}

cpu_capabilities detect_amd()
{
    cpu_capabilities caps;
    console::print(u" > AMD CPU detected.\n\r");
    caps.manufacturer = cpu_manufacturer::amd;
    return caps;
}

void detect_brand(cpu_capabilities & caps)
{
    auto buf = reinterpret_cast<std::uint32_t *>(caps.brand_string);

    for (auto i = 0x80000002; i <= 0x80000004; ++i)
    {
        std::uint64_t registers[4];
        cpuid(i, registers[0], registers[1], registers[2], registers[3]);

        for (int j = 0; j < 4; ++j)
        {
            *buf++ = registers[j] & 0xffffffff;
        }
    }
}

cpu_capabilities detect_cpu()
{
    std::uint64_t rbx, _;
    cpuid(0, _, rbx, _, _);

    auto caps = [&]() -> cpu_capabilities {
        switch (rbx)
        {
            case 0x756e6547:
                return detect_intel();

            case 0x68747541:
                return detect_amd();

            default:
                console::print(u" > Unknown CPU manufacturer detected.\n\r");
                return {};
        }
    }();

    std::uint64_t rax;
    cpuid(0x80000000, rax, _, _, _);
    if (rax >= 0x80000004)
    {
        detect_brand(caps);
    }

    console::print(u" > CPU brand string: ", caps.brand_string, u"\n\r");

    return caps;
}
}
