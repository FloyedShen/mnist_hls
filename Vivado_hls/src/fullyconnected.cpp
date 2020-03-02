#include "fullyconnected.h"

void Fully_Connected_Layer_1(hw_fixed input_feature[image_Batch][CONV_3_TYPE],
		const hw_fixed* weights,
		const hw_fixed* bias,
		hw_fixed output_feature[image_Batch][OUTPUT_NN_1_SIZE]){

	for (int batch = 0; batch < image_Batch; batch++) {
			for (int i = 0; i < OUTPUT_NN_1_SIZE; i++) {
				hw_fixed temp = 0;
				for (int j = 0; j < INPUT_NN_1_SIZE; j++) {
#pragma HLS pipeline
					hw_fixed in_val = input_feature[batch][j];
					hw_fixed w_val = weights[j*84+i];
					temp += in_val*w_val;
				}
				output_feature[batch][i] = _tanh(temp + bias[i]);
			}
		}
}
void Fully_Connected_Layer_2(hw_fixed input_feature[image_Batch][OUTPUT_NN_1_SIZE],
		const hw_fixed* weights,
		const hw_fixed* bias,
		hw_fixed* output_feature){

	for (int batch = 0; batch < image_Batch; batch++) {
		for (int i = 0; i < OUTPUT_NN_2_SIZE; i++) {
			hw_fixed temp = 0;
			for (int j = 0; j < INPUT_NN_2_SIZE; j++) {
#pragma HLS pipeline
				hw_fixed in_val = input_feature[batch][j];
				hw_fixed w_val = weights[j*10+i];
				temp += in_val*w_val;//input_feature[batch*84 + j] * weights[j*10 + i];
			}
			output_feature[batch*10 + i] = _tanh(temp + bias[i]);
		}
	}
}


