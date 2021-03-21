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

#include "../include/crypto/crc32.h"

static const constexpr std::uint32_t ethernet_polynomial_le = 0xEDB88320;

namespace crypto {
std::uint32_t crc32le_hole(std::uint8_t * data, std::size_t len, std::size_t skip_offset, std::size_t skip_length)
{
    std::uint32_t crc = ~0;

    while(len--) {
        auto cur_byte = *data++;

        if(skip_offset == 0 && skip_length--)
            cur_byte = 0;
        else
            --skip_offset;

        for (auto bit = 8; bit--; cur_byte >>= 1) {
            if ((crc ^ cur_byte) & 1) {
                crc >>= 1;
                crc ^= ethernet_polynomial_le;
            } else
                crc >>= 1;
        }
    }

    return crc;
}
}
