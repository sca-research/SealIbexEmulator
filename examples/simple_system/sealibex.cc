#include "sealibex.h"
#include "seal/seal.h"
#include "seal/emulator.h"

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
#define SEAL_TRACE "./ibex_seal.trace"  //Output Seal trace path.


using namespace std;


Seal *seal = NULL;             //Seal kernel.


//Exported core status from verilated code.
struct {
    //Simulation Time.
    uint32_t SimTime;

    //Register files.
    uint32_t Reg[NUM_REG];      //General registers.
    uint32_t WbReg;             //Writeback register.

    //Pipeline registers.
    uint32_t F2DReg; //Fetch-Decode register.

    //Execution ALU
    //uint8_t ExeInst;
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
    seal = InitSeal(IBEX_CORE_SPEC, SEAL_TRACE, SEAL_TRACE_MODE_CREATE);

#ifdef DBG
    //DBG
    SealSetVerbose(true);
#endif

    //Bind Seal components to exported rv_core.
    SealBind(seal, "SimTime", &rv_core.SimTime);
    SealBind(seal, "Reg", rv_core.Reg);
    SealBind(seal, "WbReg", &rv_core.WbReg);
    SealBind(seal, "F2DReg", &rv_core.F2DReg);
    //SealBind(seal, "ExeInst", &rv_core.ExeInst);
    SealBind(seal, "ExeOpA", &rv_core.ExeOpA);
    SealBind(seal, "ExeOpB", &rv_core.ExeOpB);
    SealBind(seal, "ExeResult", &rv_core.ExeResult);
    SealBind(seal, "MemInstRdBus", &rv_core.MemInstRdBus);
    SealBind(seal, "MemDataRdBus", &rv_core.MemDataRdBus);
    SealBind(seal, "MemDataWrBus", &rv_core.MemDataWrBus);

    //Set scope to call DPI from ibex_simple_system module.
    const svScope ibexscope = svGetScopeFromName("TOP.ibex_simple_system");
    svSetScope(ibexscope);

    return;
}

//Clean Seal kernel.
void SealClean()
{
    FreeSeal(seal);
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
        rv_core.Reg[i] = GetReg(i);
    }

    //Writeback register.
    rv_core.WbReg = seal_get_wb_reg();

    //**********************
    //Pipeline registers
    //**********************
    rv_core.F2DReg = seal_get_f2d_reg();


    //**********************
    //Execution ALU
    //**********************
    //Execution instruction.
    //rv_core.ExeInst = seal_get_exe_inst();

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
    SealSync(seal);

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
        printf("0x%08X,", rv_core.Reg[i]);
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
    SealWrite(seal);
    return;
}

//Synchronise signals to Seal kernel.
void SealSync(VerilatedToplevel *vtop, time_t time)
{
    //Sync signals to Seal kernel Frame.
    SyncRvCore(time);

    //Write a Frame.
    WriteFrame();
    return;
}
