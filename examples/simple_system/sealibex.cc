#include "sealibex.h"
#include "smurf/smurf.h"
#include "smurf/emulator.h"

#include <iostream>

#include <Vibex_simple_system_ibex_simple_system.h>
#include <Vibex_simple_system.h>

using namespace std;

void SealLibTest()
{
    cout<<"#####################"<<endl;
    INFO("SealTest() invoked.\n");
    cout<<"#####################"<<endl;
    return;
}


void SealLibTest(VerilatedToplevel *vtop)
{
    Vibex_simple_system *top = (Vibex_simple_system*) vtop;
    cout<<(int)top->IO_CLK<<' '<<(int)top->IO_RST_N<<endl;
    cout<<(int)top->ibex_simple_system->clk_sys<<endl;

    return;
}

void SealInit()
{
    SmurfSetVerbose(true);
    return;
}
