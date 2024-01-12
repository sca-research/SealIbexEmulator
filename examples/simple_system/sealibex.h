#ifndef _SEALIBEX_H
#define _SEALIBEX_H

#include "smurf/smurf.h"
#include "smurf/emulator.h"

#include "ibex_simple_system.h"
#include "verilated_toplevel.h"

//Initialise Seal kernel.
void SealInit();

//Clean Seal kernel.
void SealClean();

void SealLibTest();
void SealLibTest(VerilatedToplevel * top, time_t time);

#endif
