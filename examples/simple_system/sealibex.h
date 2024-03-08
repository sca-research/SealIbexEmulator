#ifndef _SEALIBEX_H
#define _SEALIBEX_H

#include "seal/seal.h"
#include "seal/emulator.h"

#include "ibex_simple_system.h"
#include "verilated_toplevel.h"

//Initialise Seal kernel.
void SealInit();

//Clean Seal kernel.
void SealClean();

//Synchronise signals to Seal kernel.
void SealSync(VerilatedToplevel * top, time_t time);

#endif
