/*
 * Copyright © 2021 Michał 'Griwes' Dominiak
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <cstdint>

namespace reaveros::loader
{
enum class memory_type : std::uint32_t {
    reaveros_kernel = 0x80000000,
    reaveros_initrd = 0x80000001,
    reaveros_framebuffer = 0x80000002,
};

// As in EFI_MEMORY_DESCRIPTOR::Attribute
enum class memory_cacheability : std::uint8_t {
    not_cacheable = 1 << 0,
    write_combining = 1 << 1,
    write_through = 1 << 2,
    write_back = 1 << 3,
    not_cacheable_exported_fetch_and_add = 1 << 4,
};

enum class memory_protection : std::uint8_t {
    write_protect = 1 << 0,
    read_protect = 1 << 1,
    execute_protect = 1 << 2,
    read_only = 1 << 3,
};

struct memory_map {
    memory_type type;
    std::uint64_t start_physical;
    std::uint64_t start_virtual;
    std::uint64_t count;

    memory_cacheability cacheability;
    memory_protection protection;
    bool specific_purpose;
    bool crypto;
    bool non_volatile;
    bool need_runtime_mapping;
};



inline memory_cacheability operator|(memory_cacheability lhs, memory_cacheability rhs)
{
    return static_cast<memory_cacheability>(static_cast<std::uint8_t>(lhs) | static_cast<std::uint8_t>(rhs));
}

inline memory_cacheability & operator|=(memory_cacheability & self, memory_cacheability other)
{
    return self = self | other;
}

inline memory_protection operator|(memory_protection lhs, memory_protection rhs)
{
    return static_cast<memory_protection>(static_cast<std::uint8_t>(lhs) | static_cast<std::uint8_t>(rhs));
}

inline memory_protection & operator|=(memory_protection & self, memory_protection other)
{
    return self = self | other;
}
}
