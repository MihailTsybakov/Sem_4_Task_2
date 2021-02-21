#include "Autotest.h"

bool autotest()
{
    bool pass_flag = true;

    CIntN0 Number_1(4, true, "1438", "-");
    CIntN0 Number_2(4, true, "2873", "-");
    CIntN0 Number_3(4, false, "1332", "-"); // -1332
    CIntN0 Number_4(4, false, "4312", "-"); // -4312

    // 1) "+" + "+", 4311
    CIntN0 Result = Number_1 + Number_2;
    if (int(Result) != 4311) pass_flag = false;

    // 2) "+" - "+"
    Result = Number_1 - Number_2; // -1435
    if (int(Result) != -1435) pass_flag = false;

    Result = Number_2 - Number_1; // 1435
    if (int(Result) != 1435) pass_flag = false;


    // 3) "+" + "-"
    Result = Number_1 + Number_3; // 0106
    if (int(Result) != 106) pass_flag = false;


    Result = Number_1 + Number_4; // -2874
    if (int(Result) != -2874) pass_flag = false;


    // 4) "-" + "+"
    Result = Number_4 + Number_2; //-1439
    if (int(Result) != -1439) pass_flag = false;


    /// ******** - ********
    // 5) "-" - "-"
    Result = Number_3 - Number_4; // 2980
    if (int(Result) != 2980) pass_flag = false;

    Result = Number_4 - Number_3; // -2980
    if (int(Result) != -2980) pass_flag = false;

    // 6) "+" - "-"
    Result = Number_1 - Number_4; // 5750
    if (int(Result) != 5750) pass_flag = false;

    // 7) "-" - "+"
    Result = Number_4 - Number_1; // -5750
    if (int(Result) != -5750) pass_flag = false;

    //8 ) "-" + "-"
    Result = Number_3 + Number_4; // -5644
    if (int(Result) != -5644) pass_flag = false;


    return pass_flag;
}
