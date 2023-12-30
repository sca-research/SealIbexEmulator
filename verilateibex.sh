#!/bin/bash

fusesoc --cores-root=. run --target=sim --setup --build lowrisc:ibex:ibex_simple_system $(util/ibex_config.py small fusesoc_opts)
