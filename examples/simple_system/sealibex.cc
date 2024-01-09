#include "sealibex.h"
#include "smurf/smurf.h"
#include "smurf/emulator.h"

#include <iostream>

#include "Vibex_simple_system.h"
#include "Vibex_simple_system_ibex_simple_system.h"
//#include "Vibex_simple_system_ibex_top_tracing__pi1.h"

#include "svdpi.h"
#include "Vibex_simple_system__Dpi.h"

using namespace std;

void SealLibTest()
{
    cout << "#####################" << endl;
    INFO("SealTest() invoked.\n");
    cout << "#####################" << endl;
    return;
}

void SealLibTest(VerilatedToplevel *vtop, time_t time)
{
    //Entrance to top level ibex_simple_system module.
    Vibex_simple_system *top = (Vibex_simple_system *) vtop;
    Vibex_simple_system_ibex_simple_system const *ibextop =
        top->ibex_simple_system;

    //cout<<time<<" (IO_CLK, IO_RST_N): "<<"("<<ibextop->IO_CLK<<","<<ibextop->IO_RST_N<<")"<<endl;
    //cout<<time<<" clk_sys: "<<ibextop->clk_sys<<endl;
    //cout<<time<<" RegFile: "<<ibextop->RegFile<<endl;
    //cout<<time<<" host_wdata: " << (uint32_t)(ibextop->host_wdata[0]) << endl;
    //cout<<time<<" host_rdata: " << (uint32_t)(ibextop->host_rdata[0]) << endl;
    //cout<<time<<" timer_irq: " << ibextop->timer_irq << endl;
    //cout<<time<<" u_top.clk_i: " << ibextop->u_top->clk_i << endl;

    const svScope ibexscope = svGetScopeFromName("TOP.ibex_simple_system");
    svSetScope(ibexscope);

    uint64_t cycle = seal_get_reg(1);
    cout << time << " dpi::seal_get_reg: " << cycle << endl;

    return;
}

void SealInit()
{
    SmurfSetVerbose(true);
    return;
}
