#!/usr/bin/python3
# A script to generate an Ibex core specification.

import seal


ibex_core = seal.Core(ver=2)

# Simulation time.
ibex_core.NewComponent("SimTime", "UINT32")

# 32 general register files.
ibex_core.NewComponent("Reg", "UINT32", 32)

# Writeback register.
ibex_core.NewComponent("WbReg", "UINT32")

# Fetch-Decode register.
ibex_core.NewComponent("F2DReg", "UINT32")

# Execution instruction.
# ibex_core.NewComponent("ExeInst", "OCTET")

# Execution operands.
ibex_core.NewComponent("ExeOpA", "UINT32")
ibex_core.NewComponent("ExeOpB", "UINT32")

# Execution result.
ibex_core.NewComponent("ExeResult", "UINT32")

# Instruction memory read bus.
ibex_core.NewComponent("MemInstRdBus", "UINT32")

# Data memory read bus.
ibex_core.NewComponent("MemDataRdBus", "UINT32")

# Data memory read bus.
ibex_core.NewComponent("MemDataWrBus", "UINT32")

# Save the Core Specification.
ibex_core.Save("./ibex.scs")
