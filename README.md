# mnist_hls
 Lenet for MNIST handwritten digit recognition using Vivado hls tool

## requirement
* Vivado hls 2019.2
* Vitis 2019.2

## usage
* Download MNIST data set from [MNIST](http://yann.lecun.com/exdb/mnist/)
* build hls project
```
# When you are in the project root directory
vivado_hls -f script.tcl
```
* Then you can generate LeNet IP from the project.

## TODO
* Use fixed-point numbers instead of floating-point numbers.
* Complete PS part design.