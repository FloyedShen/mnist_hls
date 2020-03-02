/*
 * LeNet.h
 *
 *  Created on: 2020. 2. 27.
 *      Author: floyed
 */
#ifndef __LENET_H__
#define __LENET_H__

//system
#include "ap_int.h"
#include "ap_axi_sdata.h"

//parameters
#include "parameters.h"

//layers
#include "activation.h"
#include "convolution.h"
#include "fullyconnected.h"
#include "pooling.h"

void LeNet(ap_axis<HW_DATA_WIDTH,1,1,1>src[BUFFER_SIZE], ap_axis<HW_DATA_WIDTH,1,1,1>dst[CLASSES], int id);

#endif
