#include "CIntN_vert.h"
#include "exceptions.cpp"

int CIntN1::output(string FileName) //override
{
    ofstream output_file(FileName);
    if (!output_file.is_open())
    {
        cout << "Error: cannot open " << FileName << endl;
        exit(-1);
    }
    if (sign != true)
    {
        output_file << '-' << endl;
    }
    for (int i = 0; i < dimension; ++i)
    {
        output_file << (digits[i]) << endl;
    }
    output_file.close();
    return 0;
}

CIntN1::~CIntN1()
{
    if (dimension != 0)
    {
        delete[] digits;
        dimension = 0;
    }
}
