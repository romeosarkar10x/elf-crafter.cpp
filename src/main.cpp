#include <iostream>

#include "elf32/elf32.hpp"
#include "utility/lonifier/lonifier.hpp"

int main()
{
    using namespace elf_crafter;
    elf_crafter::elf32::elf32 elf32("temp/hello.o");

    elf32.close_file();

    /*
    lon_string s("hello_world");
    lon_object o_1, o_2, o_3;
    o_1.set_key("z", &s);

    lon_array arr;
    arr.push(new lon_string("this is another string"));

    lon_object x;
    x.set_key("key1", new lon_string("value1"));
    x.set_key("key2", new lon_string("value2"));
    arr.push(&x);

    lon_array arr2;
    x.set_key("key2", &arr2);

    o_1.set_key("arr", &arr);
    o_2.set_key("y", &o_1);
    o_3.set_key("x", &o_2);

    std::cout << (o_3 | stringifier(4u)) << std::endl;
    */
}