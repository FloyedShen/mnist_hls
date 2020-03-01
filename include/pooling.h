/*
 *  pooling.h
 *
 *  Created on: 2020. 2. 27.
 *      Author: floyed
 */

#ifndef __POOLING_H__
#define __POOLING_H__

#include "activation.h"
#include "parameters.h"

void Pooling_Layer_1(hw_fixed src[image_Batch][CONV_1_TYPE][CONV_1_OUTPUT_WH][CONV_1_OUTPUT_WH],
		const hw_fixed pool_kernel[POOL_1_TYPE*4],
		const hw_fixed pool_bias[POOL_1_TYPE],
		hw_fixed dst[image_Batch][CONV_1_TYPE][CONV_2_INPUT_WH][CONV_2_INPUT_WH]);

void Pooling_Layer_2(const hw_fixed src[image_Batch][CONV_2_TYPE][CONV_2_OUTPUT_WH][CONV_2_OUTPUT_WH],
		const hw_fixed pool_kernel[POOL_1_TYPE*4],
		const hw_fixed pool_bias[POOL_1_TYPE],
		hw_fixed dst[image_Batch][CONV_2_TYPE][CONV_3_INPUT_WH][CONV_3_INPUT_WH]);

#endif
