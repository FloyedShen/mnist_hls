# mnist_hls
 Lenet for MNIST handwritten digit recognition using Vivado hls tool. Through co-simulation, the accuracy rate is 97.5938% (8 bits).

## requirement
* Vivado hls 2019.2
* petalinux 2019.2
* Vitis 2019.2
* python 3 +

## usage
* Download MNIST dataset from [MNIST](http://yann.lecun.com/exdb/mnist/) and cpoy the dataset to '~/Vivado_hls/MNIST_DATA/'

* build hls project
```
# When you are in the project root directory
cd Vivado_hls
vivado_hls -f script.tcl
```

* Generate 'tanh' table (default: ap_fixed<8,3>)
```
# When you are in the project root directory
cd Vivado_hls/tools
python ./tanh_table.py
```

* build vivado project
```
# When you are in the project root directory
cd Vivado
vivado -source source/tcl
```

* Generate output product && export hardware.

* To be continued


## TODO
* Complete PS part design.