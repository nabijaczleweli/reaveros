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

#include "efi.h"
#include "console.h"

void efi_loader::console::initialize()
{
    system_table->ConOut->Reset(system_table->ConOut, false);
    clear();
}

void efi_loader::console::clear()
{
    system_table->ConOut->ClearScreen(system_table->ConOut);
}

void efi_loader::console::print(const char16_t * str)
{
    // the following casts away const qualifiers
    // the EFI API is very very very bad
    system_table->ConOut->OutputString(system_table->ConOut, (CHAR16 *)(str));
}

