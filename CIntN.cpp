#include "CIntN.h"
#include "exceptions.cpp"

CIntN::CIntN()
{
    sign = true;
    dimension = 0;
    digits = {};
}
CIntN::~CIntN()
{
    if (dimension != 0)
    {
        delete[] digits;
        dimension = 0;
    }
}

CIntN::CIntN(int dimension, bool sign, string digits_string, string output_file)
{
    try
    {
        this->sign = sign;
        this->dimension = dimension;
        this->output_file = output_file;
        if (static_cast<size_t>(dimension) != digits_string.size())
        {
            throw dimension_error("Error: dimension mismatch.");
        }
        digits = new int[dimension];
        for (size_t i = 0; i < digits_string.size(); ++i)
        {
            char symbol = static_cast<char>(digits_string[i]);
            if (symbol < 48 || symbol > 57)
            {
                throw wrong_input("Error: non-numeric character found.");
            }
            digits[i] = symbol - 48;
        }
    }
    catch (const exception& exc)
    {
        cerr << exc.what() << endl;
        exit(-1);
    }
}

CIntN::CIntN(const CIntN& to_copy)
{
    sign = to_copy.sign;
    dimension = to_copy.dimension;
    digits = new int[dimension];
    for (int i = 0; i < dimension; ++i)
    {
        digits[i] = to_copy.digits[i];
    }
}

CIntN& CIntN::operator=(const CIntN& equals_to)
{
    try
    {
        if (this->dimension != equals_to.dimension)
        {
            throw dimension_error("Error: dimension mismatch.");
        }
        sign = equals_to.sign;
        for (int i = 0; i < dimension; ++i)
        {
            digits[i] = equals_to.digits[i];
        }
    }
    catch (const exception& exc)
    {
        cerr << exc.what() << endl;
        exit(-1);
    }
    return *this;
}

string CIntN::out_file() const noexcept
{
    return output_file;
}

void CIntN::print() const noexcept
{
    if (dimension == 0)
    {
        return;
    }
    if (sign != true)
    {
        cout << "-";
    }
    for (int i = 0; i < dimension; ++i)
    {
        cout << digits[i];
    }
    cout << endl;
}

int CIntN::getabs() const noexcept
{
    int num = 0;
    for (int i = dimension - 1; i >= 0; --i)
    {
        num += digits[i]*pow(10, dimension-1-i);
    }
    return num;
}

CIntN::operator int() const noexcept
{

    int num = 0;
    for (int i = dimension - 1; i >= 0; --i)
    {
        num += digits[i]*pow(10, dimension-1-i);
    }
    sign == true? num *= 1 : num *= -1;
    return num;
}
string CIntN::pure_plus(const CIntN& num_1, const CIntN& num_2)
{
    int* res_digits = new int[num_1.dimension];
    for (int i = 0; i < num_1.dimension; ++i)
    {
        res_digits[i] = 0;
    }
    for (int i = num_1.dimension - 1; i >= 0; --i)
    {
        int sum = num_1.digits[i] + num_2.digits[i];
        if (sum > 9)
        {
            if (i == 0)
            {
                 for (int j = 0; j < num_1.dimension; ++j)
                {
                    res_digits[i] = 9;
                }
            }
            else
            {
                res_digits[i] += sum - 10;
                res_digits[i - 1] = 1;
            }
        }
        else
        {
            res_digits[i] += sum;
        }
    }
    string res_sdigits = "";
    for (int i = 0; i < num_1.dimension; ++i)
    {
        res_sdigits += static_cast<char>(res_digits[i] + 48);
    }
    delete[] res_digits;
    return res_sdigits;
}

string CIntN::pure_minus(const CIntN& num_1, const CIntN& num_2)
{
    int* res_digits = new int[num_1.dimension];
    int* digits_1 = new int[num_1.dimension], *digits_2 = new int[num_1.dimension];
    for (int i = 0; i < num_1.dimension; ++i)
    {
        digits_1[i] = num_1.digits[i];
        digits_2[i] = num_2.digits[i];
        res_digits[i] = 0;
    }
    bool sign = true;
    if (num_1.getabs() < num_2.getabs())
    {
        sign = false;
        int* tmp = digits_2;
        digits_2 = digits_1;
        digits_1 = tmp;
    }
    for (int i = 0; i < num_1.dimension; ++i)
    {
        int delta = digits_1[i] - digits_2[i];
        if (delta >= 0)
        {
            res_digits[i] = delta;
        }
        else
        {
            res_digits[i] = 10 + delta;
            int j = i - 1;
            while (res_digits[j] == 0)
            {
                j--;
            }
            res_digits[j] -= 1;
            j++;
            while (j < i)
            {
                res_digits[j] = 9;
                j++;
            }
        }
    }
    string res_sdigits = "";
    if (sign != true)
    {
        res_sdigits += '-';
    }
    for (int i = 0; i < num_1.dimension; ++i)
    {
        res_sdigits += static_cast<char>(res_digits[i] + 48);
    }
    delete[] res_digits;
    delete[] digits_1;
    delete[] digits_2;
    return res_sdigits;
}
/// *************************************

CIntN0 CIntN0::operator+(const CIntN0& addition)
{
    try
    {
        if (dimension != addition.dimension)
        {
            throw dimension_error("Error: dimension mismatch in operator+.");
        }
        // "+" + "+"
        if (sign == true && addition.sign == true)
        {
            string res_digits = pure_plus(*this, addition);
            return CIntN0(dimension, true, res_digits, output_file);
        }
        // "+" + "-"
        if (sign == true && addition.sign == false)
        {
            string res_digits = pure_minus(*this, addition);
            if (res_digits[0] == '-')
            {
                return CIntN0(dimension, false, res_digits.substr(1, res_digits.size()-1), output_file);
            }
            return CIntN0(dimension, true, res_digits, output_file);
        }
        // "-" + "+"
        if (sign == false && addition.sign == true)
        {
            string res_digits = pure_minus(addition, *this);
            if (res_digits[0] == '-')
            {
                return CIntN0(dimension, false, res_digits.substr(1, res_digits.size()-1), output_file);
            }
            return CIntN0(dimension, true, res_digits, output_file);
        }
        // "-" + "-"
        if (sign == false && addition.sign == false)
        {
            string res_digits = pure_plus(*this, addition);
            return CIntN0(dimension, false, res_digits, output_file);
        }
    }
    catch (const exception& exc)
    {
        cerr << exc.what() << endl;
        exit(-1);
    }
}

CIntN0 CIntN0::operator-(const CIntN0& subtraction)
{
    try
    {
        if (dimension != subtraction.dimension)
        {
            throw dimension_error("Error: dimension mismatch in operator -.");
        }
        // "+" - "+"
        if (sign == true && subtraction.sign == true)
        {
            string res_digits = pure_minus(*this, subtraction);
            if (res_digits[0] == '-')
            {
                return CIntN0(dimension, false, res_digits.substr(1, res_digits.size()-1), output_file);
            }
            return CIntN0(dimension, true, res_digits, output_file);
        }
        // "+" - "-"
        if (sign == true && subtraction.sign == false)
        {
            string res_digits = pure_plus(*this, subtraction);
            return CIntN0(dimension, true, res_digits, output_file);
        }
        // "-" - "+"
        if (sign == false && subtraction.sign == true)
        {
            string res_digits = pure_plus(*this, subtraction);
            return CIntN0(dimension, false, res_digits, output_file);
        }
        // "-" - "-"
        if (sign == false && subtraction.sign == false)
        {
            string res_digits = pure_minus(subtraction, *this);
            if (res_digits[0] == '-')
            {
                return CIntN0(dimension, false, res_digits.substr(1, res_digits.size()-1), output_file);
            }
            return CIntN0(dimension, true, res_digits, output_file);
        }
    }
    catch (const exception& exc)
    {
        cerr << exc.what() << endl;
        exit(-1);
    }
}

CIntN1 CIntN1::operator+(const CIntN1& addition)
{
    try
    {
        if (dimension != addition.dimension)
        {
            throw dimension_error("Error: dimension mismatch in operator+.");
        }
        // "+" + "+"
        if (sign == true && addition.sign == true)
        {
            string res_digits = pure_plus(*this, addition);
            return CIntN1(dimension, true, res_digits, output_file);
        }
        // "+" + "-"
        if (sign == true && addition.sign == false)
        {
            string res_digits = pure_minus(*this, addition);
            if (res_digits[0] == '-')
            {
                return CIntN1(dimension, false, res_digits.substr(1, res_digits.size()-1), output_file);
            }
            return CIntN1(dimension, true, res_digits, output_file);
        }
        // "-" + "+"
        if (sign == false && addition.sign == true)
        {
            string res_digits = pure_minus(addition, *this);
            if (res_digits[0] == '-')
            {
                return CIntN1(dimension, false, res_digits.substr(1, res_digits.size()-1), output_file);
            }
            return CIntN1(dimension, true, res_digits, output_file);
        }
        // "-" + "-"
        if (sign == false && addition.sign == false)
        {
            string res_digits = pure_plus(*this, addition);
            return CIntN1(dimension, false, res_digits, output_file);
        }
    }
    catch (const exception& exc)
    {
        cerr << exc.what() << endl;
        exit(-1);
    }
}

CIntN1 CIntN1::operator-(const CIntN1& subtraction)
{
    try
    {
        if (dimension != subtraction.dimension)
        {
            throw dimension_error("Error: dimension mismatch in operator -.");
        }
        // "+" - "+"
        if (sign == true && subtraction.sign == true)
        {
            string res_digits = pure_minus(*this, subtraction);
            if (res_digits[0] == '-')
            {
                return CIntN1(dimension, false, res_digits.substr(1, res_digits.size()-1), output_file);
            }
            return CIntN1(dimension, true, res_digits, output_file);
        }
        // "+" - "-"
        if (sign == true && subtraction.sign == false)
        {
            string res_digits = pure_plus(*this, subtraction);
            return CIntN1(dimension, true, res_digits, output_file);
        }
        // "-" - "+"
        if (sign == false && subtraction.sign == true)
        {
            string res_digits = pure_plus(*this, subtraction);
            return CIntN1(dimension, false, res_digits, output_file);
        }
        // "-" - "-"
        if (sign == false && subtraction.sign == false)
        {
            string res_digits = pure_minus(subtraction, *this);
            if (res_digits[0] == '-')
            {
                return CIntN1(dimension, false, res_digits.substr(1, res_digits.size()-1), output_file);
            }
            return CIntN1(dimension, true, res_digits, output_file);
        }
    }
    catch (const exception& exc)
    {
        cerr << exc.what() << endl;
        exit(-1);
    }
}

/// *************************************
CIntN0::~CIntN0()
{
    if (dimension != 0)
    {
        delete[] digits;
        dimension = 0;
    }
}

CIntN1::~CIntN1()
{
    if (dimension != 0)
    {
        delete[] digits;
        dimension = 0;
    }
}

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

CIntN* Hori_Factory::create_CINT(int dimension, bool sign, string digits_string, string output_file) const noexcept
{
    return new CIntN0(dimension, sign, digits_string, output_file);
}

CIntN* Vert_Factory::create_CINT(int dimension, bool sign, string digits_string, string output_file) const noexcept
{
    return new CIntN1(dimension, sign, digits_string, output_file);
}

