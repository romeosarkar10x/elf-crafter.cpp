#include <iostream>

#include "elf32/elf32.hpp"

int main()
{
    elf_crafter::elf32::elf32("temp/hello.o");
}