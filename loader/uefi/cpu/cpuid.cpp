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

#include <cstdint>

#include "cpuid.h"
#include "../efi/console.h"

#define cpuid(id, a, b, c, d) \
    asm volatile("cpuid" : "=a"(a), "=b"(b), "=c"(c), "=d"(d) : "a"(id));

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
}

efi_loader::cpu_capabilities efi_loader::detect_cpu()
{
    std::uint64_t rbx, _;
    cpuid(0, _, rbx, _, _);

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
}

