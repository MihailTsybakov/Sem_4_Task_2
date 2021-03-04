#include "Factory.h"

CIntN* Hori_Factory::create_CINT(int dimension, bool sign, string digits_string, string output_file) const noexcept
{
    return new CIntN0(dimension, sign, digits_string, output_file);
}

CIntN* Vert_Factory::create_CINT(int dimension, bool sign, string digits_string, string output_file) const noexcept
{
    return new CIntN1(dimension, sign, digits_string, output_file);
}
