#include "sealibex.h"
#include "smurf/smurf.h"
#include "smurf/emulator.h"

#include <iostream>
#include <iomanip>
#include <cstdio>

//#include "Vibex_simple_system.h"
//#include "Vibex_simple_system_ibex_simple_system.h"
//#include "Vibex_simple_system_ibex_top_tracing__pi1.h"

#include "svdpi.h"
#include "Vibex_simple_system__Dpi.h"

#define NUM_REG (32)            //Number of registers.

using namespace std;

void SealInit()
{
    SmurfSetVerbose(true);

    //Set scope to call DPI from ibex_simple_system module.
    const svScope ibexscope = svGetScopeFromName("TOP.ibex_simple_system");
    svSetScope(ibexscope);

    return;
}

void SealLibTest()
{
    cout << "#####################" << endl;
    INFO("SealTest() invoked.\n");
    cout << "#####################" << endl;
    return;
}

//Read the value in register[regindex] ranged from 0 to 31.
uint32_t GetReg(int regindex)
{
    //Access with DPI.
    return seal_get_reg(regindex);
}

void SealLibTest(VerilatedToplevel *vtop, time_t time)
{
    uint32_t reg[NUM_REG] = { 0 };

    for (int i = 0; i < NUM_REG; i++)
    {
        reg[i] = GetReg(i);
    }

    //Print regs.
    cout << oct << time << " Regs: [";
    for (int i = 0; i < NUM_REG; i++)
    {
        printf("0x%08X,", reg[i]);
    }

    cout << "]" << endl;

    return;
}
