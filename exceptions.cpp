#ifndef EXCEPTION
#define EXCEPTION
#include <string>

class dimension_error: public std::exception
{
private:
    std::string error_msg;
public:
    dimension_error(std::string error_msg)
    {
        this->error_msg = error_msg;
    }
    const char* what() const noexcept override
    {
        return error_msg.c_str();
    }
};

class wrong_input: public std::exception
{
private:
    std::string error_msg;
public:
    wrong_input(std::string error_msg)
    {
        this->error_msg = error_msg;
    }
    const char* what() const noexcept override
    {
        return error_msg.c_str();
    }
};


#endif //EXCEPTION
