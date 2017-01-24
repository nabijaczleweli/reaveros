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

#include "console.h"
#include "efi.h"
#include "system_table.h"

namespace efi_loader
{
using EFI_TEXT_RESET = EFIAPI EFI_STATUS (*)(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL * self, bool extended_verification);
using EFI_TEXT_STRING = EFIAPI EFI_STATUS (*)(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL * self, const char16_t * string);

using EFI_TEXT_TEST_STRING = void (*)();
using EFI_TEXT_QUERY_MODE = void (*)();
using EFI_TEXT_SET_MODE = void (*)();
using EFI_TEXT_SET_ATTRIBUTE = void (*)();

using EFI_TEXT_CLEAR_SCREEN = EFIAPI EFI_STATUS (*)(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL * self);

using EFI_TEXT_SET_CURSOR_POSITION = void (*)();
using EFI_TEXT_ENABLE_CURSOR = void (*)();

struct SIMPLE_TEXT_OUTPUT_MODE;

struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
{
    EFI_TEXT_RESET reset;
    EFI_TEXT_STRING output_string;
    EFI_TEXT_TEST_STRING test_string;
    EFI_TEXT_QUERY_MODE query_mode;
    EFI_TEXT_SET_MODE set_mode;
    EFI_TEXT_SET_ATTRIBUTE set_attribute;
    EFI_TEXT_CLEAR_SCREEN clear_screen;
    EFI_TEXT_SET_CURSOR_POSITION set_cursor_position;
    EFI_TEXT_ENABLE_CURSOR enable_cursor;
    SIMPLE_TEXT_OUTPUT_MODE * mode;
};

void console::initialize()
{
    system_table->con_out->reset(system_table->con_out, false);
    clear();
}

void console::clear()
{
    system_table->con_out->clear_screen(system_table->con_out);
}

void console::print(const char16_t * str)
{
    system_table->con_out->output_string(system_table->con_out, str);
}
}
