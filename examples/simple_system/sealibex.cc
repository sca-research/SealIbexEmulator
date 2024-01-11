#include "sealibex.h"
#include "smurf/smurf.h"
#include "smurf/emulator.h"

#include <iostream>
#include <iomanip>
#include <cstdio>

//#include "Vibex_simple_system.h"
//#include "Vibex_simple_system_ibex_simple_system.h"
//#include "Vibex_simple_system_ibex_top_tracing__pi1.h"

#ifndef DBG
#define DBG 1
#endif

#include "svdpi.h"
#include "Vibex_simple_system__Dpi.h"

#define NUM_REG (32)            //Number of registers.

#define IBEX_CORE_SPEC "seal/ibex.scs"  //Path to Ibex Seal Core Specification.
#define SEAL_TRACE "/tmp/ibex_seal.trace"       //Output Seal trace path.

using namespace std;

Smurf *seal = NULL;             //Seal kernel.

//Exported core status from verilated code.
struct {
    uint32_t SimTime;           //Simulation Time.
    uint32_t reg[NUM_REG];      //General registers.

    //Execution ALU
    uint8_t ExeInst;
    uint32_t ExeOpA;
    uint32_t ExeOpB;
    uint32_t ExeResult;

    //Memory
    uint32_t MemInstRdBus;
    uint32_t MemDataRdBus;
    uint32_t MemDataWrBus;
} rv_core = { 0 };

//Initialise Seal kernel.
void SealInit()
{
    //Initialise Seal session.
    seal = InitSmurf(IBEX_CORE_SPEC, SEAL_TRACE, SMURF_TRACE_MODE_CREATE);

#ifdef DBG
    //DBG
    SmurfSetVerbose(true);
#endif

    //Bind Seal components to exported rv_core.
    SmurfBind(seal, "SimTime", &rv_core.SimTime);
    SmurfBind(seal, "Reg", rv_core.reg);
    SmurfBind(seal, "ExeInst", &rv_core.ExeInst);
    SmurfBind(seal, "ExeOpA", &rv_core.ExeOpA);
    SmurfBind(seal, "ExeOpB", &rv_core.ExeOpB);
    SmurfBind(seal, "ExeResult", &rv_core.ExeResult);
    SmurfBind(seal, "MemInstRdBus", &rv_core.MemInstRdBus);
    SmurfBind(seal, "MemDataRdBus", &rv_core.MemDataRdBus);
    SmurfBind(seal, "MemDataWrBus", &rv_core.MemDataWrBus);

    //Set scope to call DPI from ibex_simple_system module.
    const svScope ibexscope = svGetScopeFromName("TOP.ibex_simple_system");
    svSetScope(ibexscope);

    return;
}

//Clean Seal kernel.
void SealClean()
{
    FreeSmurf(seal);
    return;
}

//Read the value in register[regindex] ranged from 0 to 31.
uint32_t GetReg(int regindex)
{
    //Access with DPI.
    return seal_get_reg(regindex);
}

//Synchronise rv_core from verilated Vibex top, then to Seal kernel.
void SyncRvCore(time_t time)
{
    //Sync from Vibex top to rv_core.

    //Simulation Time.
    rv_core.SimTime = time;

    //General registers.
    for (int i = 0; i < NUM_REG; i++)
    {
        rv_core.reg[i] = GetReg(i);
    }

    //**********************
    //Execution ALU
    //**********************

    //Execution instruction.
    rv_core.ExeInst = seal_get_exe_inst();

    //Execution operands.
    rv_core.ExeOpA = seal_get_exe_op_a();
    rv_core.ExeOpB = seal_get_exe_op_b();

    //Execution result.
    rv_core.ExeResult = seal_get_exe_result();

    //**********************
    //Memory
    //**********************

    //Instruction memory read.
    rv_core.MemInstRdBus = seal_get_mem_inst_rd();
    //Instruction memory read.
    rv_core.MemDataRdBus = seal_get_mem_data_rd();
    //Instruction memory read.
    rv_core.MemDataWrBus = seal_get_mem_data_wr();

    //Sync from rv_core to Seal kernel.
    SmurfSync(seal);

    return;
}

//Display rv_core.
void DisplayRvCore(time_t time)
{
#ifdef DBG
    //General regs.
    cout << oct << time << " Regs: [";
    for (int i = 0; i < NUM_REG; i++)
    {
        printf("0x%08X,", rv_core.reg[i]);
    }
    cout << "]" << endl;

    //Execution operands.
    printf("ExeOp: [0x%08X, 0x%08X]\n", rv_core.ExeOpA, rv_core.ExeOpB);
#endif
    return;
}

//Write a Frame into Trace.
void WriteFrame()
{
    SmurfWrite(seal);
    return;
}

void SealLibTest()
{
    cout << "#####################" << endl;
    INFO("SealTest() invoked.\n");
    cout << "#####################" << endl;
    return;
}

void SealLibTest(VerilatedToplevel *vtop, time_t time)
{
    SyncRvCore(time);
    //DisplayRvCore(time);
    WriteFrame();
    return;
}
