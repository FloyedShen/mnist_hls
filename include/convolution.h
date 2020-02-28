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

void Convolution_Layer_1(const float input_feature[image_Batch*CONV_1_INPUT_WH*CONV_1_INPUT_WH],
		const float weights[6*5*5],
		const float bias[6],
		float output_feature[image_Batch*6*CONV_1_OUTPUT_WH*CONV_1_OUTPUT_WH], int init
		);

void Convolution_Layer_2(const float input_feature[image_Batch*6*14*14],
		const float weights[6*16*5*5],
		const float bias[CONV_2_TYPE],
		float output_feature[image_Batch*16*10*10], int init
		);

void Convolution_Layer_3(const float input_feature[image_Batch*16*5*5],
		const float weights[16*120*5*5],
		const float bias[120],
		float output_feature[image_Batch*120], int init
		);

#endif
