/*
 * convolution.h
 *
 *  Created on: 2020. 2. 27.
 *      Author: floyed
 */
#ifndef __CONVOLUTION_H__
#define __CONVOLUTION_H__

#include "parameters.h"
#include "activation.h"
#include "ap_int.h"
#define CONV_2_SIZE 25

void Convolution_Layer_1(const hw_fixed IBRAM[image_Batch][CONV_1_INPUT_WH][CONV_1_INPUT_WH],
		const hw_fixed WBRAM[CONV_1_TYPE][CONV_1_WH][CONV_1_WH],
		const hw_fixed biasBRAM[CONV_1_TYPE],
		hw_fixed OBRAM[image_Batch][CONV_1_TYPE][CONV_1_OUTPUT_WH][CONV_1_OUTPUT_WH]
		);

void Convolution_Layer_2(const hw_fixed IBRAM[image_Batch][CONV_1_TYPE][CONV_2_INPUT_WH][CONV_2_INPUT_WH],
		const hw_fixed  WBRAM[CONV_2_TYPE][CONV_1_TYPE][CONV_2_WH][CONV_2_WH],
		const hw_fixed biasBRAM[CONV_2_TYPE],
		hw_fixed OBRAM[image_Batch][CONV_2_TYPE][CONV_2_OUTPUT_WH][CONV_2_OUTPUT_WH]
		);

void Convolution_Layer_3(const hw_fixed IBRAM[image_Batch][CONV_2_TYPE][CONV_3_INPUT_WH][CONV_3_INPUT_WH],
		const hw_fixed WBRAM[CONV_3_TYPE][CONV_2_TYPE][CONV_3_WH][CONV_3_WH],
		const hw_fixed biasBRAM[CONV_3_TYPE],
		hw_fixed OBRAM[image_Batch][CONV_3_TYPE]
		);


#endif
