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

#pragma once

#include <cstddef>
#include <utility>

#include <reaver/swallow.h>
#include <reaver/unit.h>

namespace efi_loader
{
namespace console
{
    void initialize();
    void clear();

    void print(const char16_t *);
    void print(std::size_t);
    void print(void *);

    inline void print(char16_t * str)
    {
        print(static_cast<const char16_t *>(str));
    }

    template<typename T>
    void print(T * ptr)
    {
        print(reinterpret_cast<void *>(ptr));
    }

    inline void print()
    {
    }

    template<typename T, typename = decltype(std::declval<T &&>().print())>
    void print(T && t)
    {
        std::forward<T>(t).print();
    }

    template<typename... Ts>
    void print(Ts &&... ts)
    {
        reaver::swallow{ (print(std::forward<Ts>(ts)), reaver::unit{})... };
    }
}
}
