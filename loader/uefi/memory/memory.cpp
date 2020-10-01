/**
 * Reaver Project OS, Rose, Licence
 *
 * Copyright © 2017, 2019 Michał "Griwes" Dominiak
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

#include <cstddef>
#include <cstdint>

extern "C" void * memcpy(void * dest, const void * src, std::size_t count)
{
    auto dest_u8 = reinterpret_cast<std::uint8_t *>(dest);
    auto src_u8 = reinterpret_cast<const std::uint8_t *>(src);

    while (count--)
    {
        *dest_u8++ = *src_u8++;
    }

    return dest;
}

extern "C" void * memset(void * dest, int ch, std::size_t count)
{
    auto dest_u8 = reinterpret_cast<std::uint8_t *>(dest);

    while (count--)
    {
        *dest_u8 = ch;
    }

    return dest;
}

extern "C" int memcmp(const void * lhs, const void * rhs, std::size_t count)
{
    auto lhs_u8 = reinterpret_cast<const std::uint8_t *>(lhs);
    auto rhs_u8 = reinterpret_cast<const std::uint8_t *>(rhs);

    while (count--)
    {
        if (*lhs_u8 != *rhs_u8)
        {
            return *lhs_u8 - *rhs_u8;
        }
    }

    return 0;
}

extern "C" std::size_t strlen(const char * str)
{
    std::size_t ret = 0;

    while (*str++)
    {
        ++ret;
    }

    return ret;
}

extern "C" void * memchr(const void * ptr, int ch, std::size_t count)
{
    auto c = static_cast<unsigned char>(ch);
    auto cp = reinterpret_cast<const unsigned char *>(ptr);

    for (std::size_t i = 0; i < count; ++i)
    {
        if (cp[i] == c)
        {
            return const_cast<void *>(reinterpret_cast<const void *>(cp + i));
        }
    }

    return NULL;
}
