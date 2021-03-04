#ifndef CINTVERT
#define CINTVERT

#include "CIntN.h"

class CIntN1 : public CIntN
{
public:
    using CIntN::CIntN;
    using CIntN::operator=;
    CIntN1(const CIntN& to_copy) : CIntN(to_copy){}
    ~CIntN1();

    int output(string FileName) override;
};

#endif // CINTVERT
