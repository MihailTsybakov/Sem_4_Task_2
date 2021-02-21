#include "CIntN.h"
#include "Create.h"
#include "Autotest.h"

int main(int argc, char* argv[])
{
    if (!autotest())
    {
        cout << "Autotest Failed!" << endl;
        exit(-1);
    }
    cout << "Autotest passed" << endl;

    string input_filename = "Input.txt";
    ifstream input_file(input_filename);

    if (!input_file.is_open())
    {
        cout << "Error: cannot open " << input_filename << endl;
        exit(-1);
    }

    vector<string> psvector; // parameter strings vector
    string tmp_string;

    while (getline(input_file, tmp_string))
    {
        psvector.push_back(tmp_string);
    }

    /// ********************************************************

    vector<CIntN*> CINT_vector;
    map<string, CINT_Factory*> factories;
    factories["Hori"] = new Hori_Factory;
    factories["Vert"] = new Vert_Factory;

    for (vector<string>::iterator it = psvector.begin(); it != psvector.end(); ++it)
    {
        CINT_vector.push_back(Create_CINTN((*it), factories));
    }

    // Outputting
    for (vector<CIntN*>::iterator it = CINT_vector.begin(); it != CINT_vector.end(); ++it)
    {
        (*it)->output((*it)->out_file());
        delete (*it);
    }

    input_file.close();

    return 0;
}
