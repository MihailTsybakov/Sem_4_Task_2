#include "CIntN_hori.h"
#include "exceptions.cpp"

int CIntN0::output(string FileName) //override
{
    ofstream output_file(FileName);
    if (!output_file.is_open())
    {
        cout << "Error: cannot open " << FileName << endl;
        exit(-1);
    }
    if (sign != true)
    {
        output_file << '-';
    }
    for (int i = 0; i < dimension; ++i)
    {
        output_file << (digits[i]);
    }
    output_file.close();
    return 0;
}

CIntN0::~CIntN0()
{
    if (dimension != 0)
    {
        delete[] digits;
        dimension = 0;
    }
}

CIntN0 operator+(const CIntN& first, const CIntN& second)
{
    try
    {
        if (first.dimension != second.dimension)
        {
            throw dimension_error("Error: dimension mismatch in operator+.");
        }
        // "+" + "+"
        if (first.sign == true && second.sign == true)
        {
            string res_digits = first.pure_plus(first, second);
            return CIntN0(first.dimension, true, res_digits, first.output_file);
        }
        // "+" + "-" addition
        if (first.sign == true && second.sign == false)
        {
            string res_digits = first.pure_minus(first, second);
            if (res_digits[0] == '-')
            {
                return CIntN0(first.dimension, false, res_digits.substr(1, res_digits.size()-1), first.output_file);
            }
            return CIntN0(first.dimension, true, res_digits, first.output_file);
        }
        // "-" + "+"
        if (first.sign == false && second.sign == true)
        {
            string res_digits = first.pure_minus(second, first);
            if (res_digits[0] == '-')
            {
                return CIntN0(first.dimension, false, res_digits.substr(1, res_digits.size()-1), first.output_file);
            }
            return CIntN0(first.dimension, true, res_digits, first.output_file);
        }
        // "-" + "-"
        if (first.sign == false && second.sign == false)
        {
            string res_digits = first.pure_plus(first, second);
            return CIntN0(first.dimension, false, res_digits, first.output_file);
        }
    }
    catch (const exception& exc)
    {
        cerr << exc.what() << endl;
        exit(-1);
    }
}

CIntN0 operator-(const CIntN& first, const CIntN& second)
{
    try
    {
        if (first.dimension != second.dimension)
        {
            throw dimension_error("Error: dimension mismatch in operator -.");
        }
        // "+" - "+" subtraction
        if (first.sign == true && second.sign == true)
        {
            string res_digits = first.pure_minus(first, second);
            if (res_digits[0] == '-')
            {
                return CIntN0(first.dimension, false, res_digits.substr(1, res_digits.size()-1), first.output_file);
            }
            return CIntN0(first.dimension, true, res_digits, first.output_file);
        }
        // "+" - "-"
        if (first.sign == true && second.sign == false)
        {
            string res_digits = first.pure_plus(first, second);
            return CIntN0(first.dimension, true, res_digits, first.output_file);
        }
        // "-" - "+"
        if (first.sign == false && second.sign == true)
        {
            string res_digits = first.pure_plus(first, second);
            return CIntN0(first.dimension, false, res_digits, first.output_file);
        }
        // "-" - "-"
        if (first.sign == false && second.sign == false)
        {
            string res_digits = first.pure_minus(second, first);
            if (res_digits[0] == '-')
            {
                return CIntN0(first.dimension, false, res_digits.substr(1, res_digits.size()-1), first.output_file);
            }
            return CIntN0(first.dimension, true, res_digits, first.output_file);
        }
    }
    catch (const exception& exc)
    {
        cerr << exc.what() << endl;
        exit(-1);
    }
}
