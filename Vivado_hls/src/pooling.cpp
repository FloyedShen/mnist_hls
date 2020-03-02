/*
 * pooling.cpp
 *
 *  Created on: 2020. 2. 27.
 *      Author: floyed
 */


#include "pooling.h"

void Pooling_Layer_1(hw_fixed src[image_Batch][CONV_1_TYPE][CONV_1_OUTPUT_WH][CONV_1_OUTPUT_WH],
		const hw_fixed pool_kernel[POOL_1_TYPE*4],
		const hw_fixed pool_bias[POOL_1_TYPE],
		hw_fixed dst[image_Batch][CONV_1_TYPE][CONV_2_INPUT_WH][CONV_2_INPUT_WH]){

	hw_fixed value;
	for (int batch = 0; batch < image_Batch; batch++){
		for (int depth = 0; depth < POOL_1_TYPE; depth++){
			for (int row = 0; row < POOL_1_OUTPUT_WH; row++){
				for (int col = 0; col < POOL_1_OUTPUT_WH; col++){
#pragma HLS pipeline
					value = src[batch][depth][row*2][col*2]//[(depth + POOL_1_TYPE * batch)*POOL_1_INPUT_SIZE + (row * 2) * POOL_1_INPUT_WH + (col * 2)]
						+ src[batch][depth][row*2][col*2+1]//src[(depth + POOL_1_TYPE * batch)*POOL_1_INPUT_SIZE + (row * 2) * POOL_1_INPUT_WH + (col * 2 + 1)]
						+ src[batch][depth][row*2+1][col*2]//src[(depth + POOL_1_TYPE * batch)*POOL_1_INPUT_SIZE + (row * 2 + 1) * POOL_1_INPUT_WH + (col * 2)]
						+ src[batch][depth][row*2+1][col*2+1];//src[(depth + POOL_1_TYPE * batch)*POOL_1_INPUT_SIZE + (row * 2 + 1) * POOL_1_INPUT_WH + (col * 2 + 1)];

					hw_fixed weight = pool_kernel[depth]*(hw_fixed)0.25;
					value *= weight;
					value += pool_bias[depth];
					dst[batch][depth][row][col] = _tanh(value);//[(batch * POOL_1_TYPE + depth)*POOL_1_OUTPUT_SIZE + row * POOL_1_OUTPUT_WH + col] = tanhf(value);
				}
			}
		}
	}
}

void Pooling_Layer_2(const hw_fixed src[image_Batch][CONV_2_TYPE][CONV_2_OUTPUT_WH][CONV_2_OUTPUT_WH],
		const hw_fixed pool_kernel[POOL_1_TYPE*4],
		const hw_fixed pool_bias[POOL_1_TYPE],
		hw_fixed dst[image_Batch][CONV_2_TYPE][CONV_3_INPUT_WH][CONV_3_INPUT_WH]){

	hw_fixed value;
	for (int batch = 0; batch < image_Batch; batch++){
		for (int depth = 0; depth < POOL_2_TYPE; depth++){
			for (int row = 0; row < POOL_2_OUTPUT_WH; row++){
				for (int col = 0; col < POOL_2_OUTPUT_WH; col++){
#pragma HLS pipeline
					value = src[batch][depth][row*2][col*2]//src[(depth + POOL_2_TYPE * batch)*POOL_2_INPUT_SIZE + (row * 2) * POOL_2_INPUT_WH + (col * 2)]
						+ src[batch][depth][row*2][col*2+1]//src[(depth + POOL_2_TYPE * batch)*POOL_2_INPUT_SIZE + (row * 2) * POOL_2_INPUT_WH + (col * 2 + 1)]
						+ src[batch][depth][row*2+1][col*2]//src[(depth + POOL_2_TYPE * batch)*POOL_2_INPUT_SIZE + (row * 2 + 1) * POOL_2_INPUT_WH + (col * 2)]
						+ src[batch][depth][row*2+1][col*2+1];//src[(depth + POOL_2_TYPE * batch)*POOL_2_INPUT_SIZE + (row * 2 + 1) * POOL_2_INPUT_WH + (col * 2 + 1)];

					hw_fixed weight = pool_kernel[depth]*(hw_fixed)0.25;
					value *= weight;
					dst[batch][depth][row][col] = _tanh(value);//[(batch * POOL_2_TYPE + depth)*POOL_2_OUTPUT_SIZE + row * POOL_2_OUTPUT_WH + col] = tanhf(value + pool_bias[depth]);
				}
			}
		}
	}
}

