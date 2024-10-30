#!/bin/bash

# This is just an example builder, adjust for your system as needed

rm -r build
source ~/.local/bin/venv/bin/activate
mkdir build &&cd build
# Ensure $PATH includes the pspdev bin/
psp-cmake -DBUILD_PRX=1
make
