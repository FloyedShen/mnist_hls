/*
 * pooling.cpp
 *
 *  Created on: 2020. 2. 27.
 *      Author: floyed
 */


#include "pooling.h"

void Pooling_Layer_1(hw_fixed* src, hw_fixed* pool_kernel, hw_fixed* pool_bias, hw_fixed* dst){
	hw_fixed value;
	for (int batch_cnt = 0; batch_cnt < image_Batch; batch_cnt++){
		for (int depth = 0; depth < POOL_1_TYPE; depth++){
			for (int row = 0; row < POOL_1_OUTPUT_WH; row++){
				for (int col = 0; col < POOL_1_OUTPUT_WH; col++){
//#pragma HLS pipeline
					value = src[(depth + POOL_1_TYPE * batch_cnt)*POOL_1_INPUT_SIZE + (row * 2) * POOL_1_INPUT_WH + (col * 2)]
						+ src[(depth + POOL_1_TYPE * batch_cnt)*POOL_1_INPUT_SIZE + (row * 2) * POOL_1_INPUT_WH + (col * 2 + 1)]
						+ src[(depth + POOL_1_TYPE * batch_cnt)*POOL_1_INPUT_SIZE + (row * 2 + 1) * POOL_1_INPUT_WH + (col * 2)]
						+ src[(depth + POOL_1_TYPE * batch_cnt)*POOL_1_INPUT_SIZE + (row * 2 + 1) * POOL_1_INPUT_WH + (col * 2 + 1)];

					hw_fixed weight = pool_kernel[depth]*(hw_fixed)0.25;
					value *= weight;
					value += pool_bias[depth];
					dst[(batch_cnt * POOL_1_TYPE + depth)*POOL_1_OUTPUT_SIZE + row * POOL_1_OUTPUT_WH + col] = tanhf(value);
				}
			}
		}
	}
}

void Pooling_Layer_2(hw_fixed* src, hw_fixed* pool_kernel, hw_fixed* pool_bias, hw_fixed* dst){
	hw_fixed value;
	for (int batch_cnt = 0; batch_cnt < image_Batch; batch_cnt++){
		for (int depth = 0; depth < POOL_2_TYPE; depth++){
			for (int row = 0; row < POOL_2_OUTPUT_WH; row++){
				for (int col = 0; col < POOL_2_OUTPUT_WH; col++){
//#pragma HLS pipeline
					value = src[(depth + POOL_2_TYPE * batch_cnt)*POOL_2_INPUT_SIZE + (row * 2) * POOL_2_INPUT_WH + (col * 2)]
						+ src[(depth + POOL_2_TYPE * batch_cnt)*POOL_2_INPUT_SIZE + (row * 2) * POOL_2_INPUT_WH + (col * 2 + 1)]
						+ src[(depth + POOL_2_TYPE * batch_cnt)*POOL_2_INPUT_SIZE + (row * 2 + 1) * POOL_2_INPUT_WH + (col * 2)]
						+ src[(depth + POOL_2_TYPE * batch_cnt)*POOL_2_INPUT_SIZE + (row * 2 + 1) * POOL_2_INPUT_WH + (col * 2 + 1)];

					hw_fixed weight = pool_kernel[depth]*(hw_fixed)0.25;
					value *= weight;
					dst[(batch_cnt * POOL_2_TYPE + depth)*POOL_2_OUTPUT_SIZE + row * POOL_2_OUTPUT_WH + col] = tanhf(value + pool_bias[depth]);
				}
			}
		}
	}
}

