############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project LeNet_hls
set_top LeNet
add_files src/LeNet.cpp -cflags "-Iinclude -Wno-unknown-pragmas"
add_files src/activation.cpp -cflags "-Iinclude -Wno-unknown-pragmas"
add_files src/convolution.cpp -cflags "-Iinclude -Wno-unknown-pragmas"
add_files src/fullyconnected.cpp -cflags "-Iinclude -Wno-unknown-pragmas"
add_files src/pooling.cpp -cflags "-Iinclude -Wno-unknown-pragmas"
add_files -tb src/LeNet_tb.cpp -cflags "-Iinclude -Wno-unknown-pragmas"
add_files -tb src/MNIST_DATA.cpp -cflags "-Iinclude -Wno-unknown-pragmas"
open_solution "origin"
set_part {xc7z020-clg484-1}
create_clock -period 10 -name default
source "./LeNet_hls/origin/directives.tcl"
csim_design -clean
csynth_design
cosim_design
export_design -format ip_catalog
