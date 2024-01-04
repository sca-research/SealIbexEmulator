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


void SealLibTest(VerilatedToplevel *vtop, time_t time)
{
    //Entrance to top level ibex_simple_system module.
    Vibex_simple_system *top = (Vibex_simple_system*) vtop;
    Vibex_simple_system_ibex_simple_system const * ibextop = top->ibex_simple_system;

    cout<<time<<" (IO_CLK, IO_RST_N): "<<"("<<ibextop->IO_CLK<<","<<ibextop->IO_RST_N<<")"<<endl;
    cout<<time<<" clk_sys: "<<ibextop->clk_sys<<endl;
    cout<<time<<" RegFile: "<<ibextop->RegFile<<endl;
    cout<<Vibex_simple_system_ibex_simple_system::bus_device_e::Ram<<endl;

    return;
}

void SealInit()
{
    SmurfSetVerbose(true);
    return;
}
