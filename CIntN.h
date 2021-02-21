/*

3. Определить класс CIntN для работы с целыми знаковыми числами,
состоящими lо N десятичных цифр, где N задается в конструкторе. В
классе должны быть определены необходимые конструкторы, деструктор, операторы присваивания, сложения, вычитания.
Написать функцию и конструктор сохранения переменной данного
типа в файл и загрузки из файла.
В отдельном файле должен быть написан тест на данный класс

*/

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <map>
#include <vector>
using namespace std;

#ifndef CINTN
#define CINTN
class CIntN
{
protected:
    int dimension;
    bool sign; // True = "+"
    int* digits; // Digits array
    string pure_plus(const CIntN& num_1, const CIntN& num_2);
    string pure_minus(const CIntN& num_1, const CIntN& num_2);
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
};

class CIntN0 : public CIntN
{
public:
    using CIntN::CIntN;
    ~CIntN0();

    int output(string FileName) override;

    CIntN0 operator+(const CIntN0& addition);
    CIntN0 operator-(const CIntN0& subtraction);
};

class CIntN1 : public CIntN
{
public:
    using CIntN::CIntN;
    ~CIntN1();

    int output(string FileName) override;

    CIntN1 operator-(const CIntN1& subtraction);
    CIntN1 operator+(const CIntN1& addition);
};

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


#endif  //CINTN
