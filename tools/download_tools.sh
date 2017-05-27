#!/bin/bash

NJOBS=8

echo $HOME/src
mkdir -p $HOME/src
cd $HOME/src

# QEMU
./install_qemu.sh

# BOCHS
./install_bochs.sh
