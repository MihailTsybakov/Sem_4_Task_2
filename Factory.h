#ifndef FACTORY
#define FACTORY

#include "CIntN_hori.h"
#include "CIntN_vert.h"

class CINT_Factory
{
public:
    virtual CIntN* create_CINT(int dimension, bool sign, string digits_string, string output_file) const noexcept = 0;
};

class Hori_Factory : public CINT_Factory
{
public:
    virtual CIntN* create_CINT(int dimension, bool sign, string digits_string, string output_file) const noexcept override;
};

class Vert_Factory : public CINT_Factory
{
public:
    virtual CIntN* create_CINT(int dimension, bool sign, string digits_string, string output_file) const noexcept override;
};

#endif // FACTORY
