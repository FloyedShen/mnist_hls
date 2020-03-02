/*
 * fullyconnected.cpp
 *
 *  Created on: 2020. 2. 27.
 *      Author: floyed
 */

#ifndef __FULLY_CONNECTED_H__
#define __FULLY_CONNECTED_H__

#include "parameters.h"
#include "activation.h"

void Fully_Connected_Layer_1(hw_fixed input_feature[image_Batch][CONV_3_TYPE],
		const hw_fixed* weights,
		const hw_fixed* bias,
		hw_fixed output_feature[image_Batch][OUTPUT_NN_1_SIZE]);

void Fully_Connected_Layer_2(hw_fixed input_feature[image_Batch][OUTPUT_NN_1_SIZE],
		const hw_fixed* weights,
		const hw_fixed* bias,
		hw_fixed* output_feature);

#endif
