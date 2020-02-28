/*
 * fullyconnected.cpp
 *
 *  Created on: 2020. 2. 27.
 *      Author: floyed
 */
#include "fullyconnected.h"

void Fully_Connected_Layer_1(float* input_feature, float* weights, float* bias, float* output_feature){
	for (int batch = 0; batch < image_Batch; batch++) {
			for (int i = 0; i < OUTPUT_NN_1_SIZE; i++) {
				float temp = 0;
				for (int j = 0; j < INPUT_NN_1_SIZE; j++) {
#pragma HLS pipeline
					float in_val = input_feature[j];
					float w_val = weights[j*84+i];
					temp += in_val*w_val;
				}
				output_feature[batch*84 + i] = tanhf(temp + bias[i]);
			}
		}
}
void Fully_Connected_Layer_2(float* input_feature, float* weights, float* bias, float* output_feature){
	for (int batch = 0; batch < image_Batch; batch++) {
		for (int i = 0; i < OUTPUT_NN_2_SIZE; i++) {
			float temp = 0;
			for (int j = 0; j < INPUT_NN_2_SIZE; j++) {
#pragma HLS pipeline
				float in_val = input_feature[j];
				float w_val = weights[j*10+i];
				temp += in_val*w_val;//input_feature[batch*84 + j] * weights[j*10 + i];
			}
			output_feature[batch*10 + i] = tanhf(temp + bias[i]);
		}
	}
}


