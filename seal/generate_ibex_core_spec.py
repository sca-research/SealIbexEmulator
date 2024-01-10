#!/usr/bin/python3
# A script to generate an Ibex core specification.

import smurf


ibex_core = smurf.Core(ver=2)

# Simulation time.
ibex_core.NewComponent("SimTime", "UINT32")

# 32 general register files.
ibex_core.NewComponent("Reg", "UINT32", 32)

# Save the Core Specification.
ibex_core.Save("./ibex.scs")
