// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
// Authors of SEAL related source code: 
// Elibsaeth Oswald (Elisabeth.Oswald@protonmail.com) and Yan Yan (yanyansmajesty@outlook.com)

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
