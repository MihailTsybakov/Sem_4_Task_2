#ifndef CREATE
#define CREATE
#include "CIntN.h"
#include "Factory.h"
vector<string> split(string source, char separator); // Splits string by separator

CIntN* Create_CINTN(string creation_parameters, map<string, CINT_Factory*> factories);

#endif // CREATE
