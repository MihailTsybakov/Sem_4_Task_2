#ifndef CINTN
#define CINTN

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <map>
#include <vector>
using namespace std;

class CIntN0;
class CIntN1;

class CIntN
{
protected:
    int dimension;
    bool sign; // True = "+"
    int* digits; // Digits array
    string pure_plus(const CIntN& num_1, const CIntN& num_2) const;
    string pure_minus(const CIntN& num_1, const CIntN& num_2) const;
    string output_file;
public:
    CIntN();
    virtual ~CIntN();
    CIntN(int dimension, bool sign, string digits_string, string output_file);
    CIntN(const CIntN& to_copy);
    CIntN& operator=(const CIntN& equals_to);
    void print() const noexcept;
    operator int() const noexcept;
    int getabs() const noexcept;
    string out_file() const noexcept;

    virtual int output(string FileName) = 0;

    friend CIntN0 operator+(const CIntN& first, const CIntN& second);
    friend CIntN0 operator-(const CIntN& first, const CIntN& second);
};

#endif  //CINTN
