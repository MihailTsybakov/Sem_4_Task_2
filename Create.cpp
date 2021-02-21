#include <Create.h>

vector<string> split(string source, char separator) // Splits string by separator
{
    vector<string> res_vector;
    size_t symbol_index = 0;
    string curr_piece = "";
    while (symbol_index < source.size())
    {
        if (source[symbol_index] != separator)
        {
            curr_piece += source[symbol_index];
        }
        else
        {
            res_vector.push_back(curr_piece);
            curr_piece = "";
        }
        symbol_index++;
    }
    res_vector.push_back(curr_piece);
    return res_vector;
}

CIntN* Create_CINTN(string creation_parameters, map<string, CINT_Factory*> factories)
{
    vector<string> parsed_params = split(creation_parameters, ' ');
    if (parsed_params.size() != 5)
    {
        cout << "Wrong parameters count." << endl;
        exit(-1);
    }
    
    int output_direction;
    parsed_params[0][0] == 'H'? output_direction = 0: output_direction = 1;
    string outfile = parsed_params[1];
    int dimension = parsed_params[2][0] - 48;
    bool sign;
    parsed_params[3][0] == 't'? sign = true : sign = false;
    string digits_string = parsed_params[4];
    
    if (output_direction == 0)
    {
        return factories["Hori"]->create_CINT(dimension, sign, digits_string, outfile);
    }
    return factories["Vert"]->create_CINT(dimension, sign, digits_string, outfile);
}
