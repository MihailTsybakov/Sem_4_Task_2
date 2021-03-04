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

    vector<CIntN*> CINT_vector;
    map<string, CINT_Factory*> factories;
    factories["Hori"] = new Hori_Factory;
    factories["Vert"] = new Vert_Factory;

    string tmp_string;

    while (getline(input_file, tmp_string))
    {
        CINT_vector.push_back(Create_CINTN(tmp_string, factories));
    }
    input_file.close();
    /// ********************************************************

    // Outputting
    for (vector<CIntN*>::iterator it = CINT_vector.begin(); it != CINT_vector.end(); ++it)
    {
        (*it)->output((*it)->out_file());
        delete (*it);
    }

    CIntN0 a(3, true, "543", "-");
    CIntN1 b(3, false, "111", "-");
    CIntN0 c = a-b;
    cout << "Frankenstein assembled from CIntN0 and CIntN1: ";
    c.print();

    return 0;
}
