/*
 * LeNet.cpp
 *
 *  Created on: 2020. 2. 27.
 *      Author: floyed
 */

/********************************************************************/
/*					correct rate: 0.975938                          */
/********************************************************************/
#include "LeNet.h"
#include "iostream"
#include "cstring"
#include "ap_fixed.h"
using namespace std;

//conv layer weight & bias
const hw_fixed Wconv1[CONV_1_TYPE][CONV_1_WH][CONV_1_WH] = {
#include "/home/parallels/Documents/LeNet/Vivado_hls/filter/Wconv1.h"
};
const hw_fixed Bconv1[CONV_1_TYPE] = {
#include "/home/parallels/Documents/LeNet/Vivado_hls/filter/bconv1.h"
};
const hw_fixed Wconv2[CONV_2_TYPE][CONV_1_TYPE][CONV_2_WH][CONV_2_WH] = {
#include "/home/parallels/Documents/LeNet/Vivado_hls/filter/Wconv3.h"
};
const hw_fixed Bconv2[CONV_2_TYPE] = {
#include "/home/parallels/Documents/LeNet/Vivado_hls/filter/bconv3.h"
};
const hw_fixed Wconv3[CONV_3_TYPE][CONV_2_TYPE][CONV_3_WH][CONV_3_WH] = {
#include "/home/parallels/Documents/LeNet/Vivado_hls/filter/Wconv5.h"
};
const hw_fixed Bconv3[CONV_3_TYPE] = {
#include "/home/parallels/Documents/LeNet/Vivado_hls/filter/bconv5.h"
};

//pool layer weight & bias
const hw_fixed Wpool1[POOL_1_TYPE*4] = {
#include "/home/parallels/Documents/LeNet/Vivado_hls/filter/Wpool1.h"
};
const hw_fixed Bpool1[POOL_1_TYPE] = {
#include "/home/parallels/Documents/LeNet/Vivado_hls/filter/bpool1.h"
};
const hw_fixed Wpool2[POOL_2_TYPE*4] = {
#include "/home/parallels/Documents/LeNet/Vivado_hls/filter/Wpool2.h"
};
const hw_fixed Bpool2[POOL_2_TYPE] = {
#include "/home/parallels/Documents/LeNet/Vivado_hls/filter/bpool2.h"
};

//fc layer weight & bias
const hw_fixed Wfc1[FILTER_NN_1_SIZE] = {
#include "/home/parallels/Documents/LeNet/Vivado_hls/filter/Wfc1.h"
};
const hw_fixed Bfc1[BIAS_NN_1_SIZE] = {
#include "/home/parallels/Documents/LeNet/Vivado_hls/filter/bfc1.h"
};
const hw_fixed Wfc2[FILTER_NN_2_SIZE] = {
#include "/home/parallels/Documents/LeNet/Vivado_hls/filter/Wfc2.h"
};
const hw_fixed Bfc2[BIAS_NN_2_SIZE] = {
#include "/home/parallels/Documents/LeNet/Vivado_hls/filter/bfc2.h"
};

//create layer
hw_fixed input[image_Batch][INPUT_WH][INPUT_WH];
hw_fixed conv1[image_Batch][CONV_1_TYPE][CONV_1_OUTPUT_WH][CONV_1_OUTPUT_WH];
hw_fixed pool1[image_Batch][CONV_1_TYPE][CONV_2_INPUT_WH][CONV_2_INPUT_WH];
hw_fixed conv2[image_Batch][CONV_2_TYPE][CONV_2_OUTPUT_WH][CONV_2_OUTPUT_WH];
hw_fixed pool2[image_Batch][CONV_2_TYPE][CONV_3_INPUT_WH][CONV_3_INPUT_WH];
hw_fixed conv3[image_Batch][CONV_3_TYPE];
hw_fixed fc1[image_Batch][OUTPUT_NN_1_SIZE];
hw_fixed output[image_Batch*OUTPUT_NN_2_SIZE];

void LeNet(ap_axis<HW_DATA_WIDTH,1,1,1>src[BUFFER_SIZE], ap_axis<HW_DATA_WIDTH,1,1,1>dst[CLASSES], int id){

	ap_axis<HW_DATA_WIDTH, 1, 1,1> data[BUFFER_SIZE];

	Copy:
	for(int i=0; i<BUFFER_SIZE; i++){
		data[i].data = src[i].data;
		data[i].dest = src[i].dest;
		data[i].id = src[i].id;
		data[i].keep = src[i].keep;
		data[i].last = src[i].last;
		data[i].strb = src[i].strb;
		data[i].user = src[i].user;
	}

	load_batch:
	for(int batch=0; batch<image_Batch; batch++){
		load_row:
		for(int i=0; i<INPUT_WH; i++){
			Load_col:
			for(int j=0; j<INPUT_WH; j++){
				int index = i*INPUT_WH+j;
				input[batch][i][j] = ((float)data[index].data)/DATA_CONVERT_MUL;
			}
		}
	}

	//cout<<"loaded image"<<endl;
	//calc
	Convolution_Layer_1(input, Wconv1, Bconv1, conv1);
	//cout<<"conv1"<<endl;
	Pooling_Layer_1(conv1, Wpool1, Bpool1, pool1);
	//cout<<"pool1"<<endl;
	Convolution_Layer_2(pool1, Wconv2, Bconv2, conv2);
	//cout<<"conv2"<<endl;
	Pooling_Layer_2(conv2, Wpool2, Bpool2, pool2);
	//cout<<"pool2"<<endl;
	Convolution_Layer_3(pool2, Wconv3, Bconv3, conv3);
	//cout<<"conv3"<<endl;
	Fully_Connected_Layer_1(conv3, Wfc1, Bfc1, fc1);
	//cout<<"fc1"<<endl;
	Fully_Connected_Layer_2(fc1, Wfc2, Bfc2, output);
	//cout<<"fc2"<<endl;

	Output:
	for(int i=0; i<CLASSES-1; i++){
//#pragma HLS pipeline
		dst[i].data = ((float)output[i])*DATA_CONVERT_MUL;//((int*)output)[i];
		//cout<<output[i]<<' '<<((float)output[i])<<' '<<((float)output[i])*DATA_CONVERT_MUL<<endl;
		dst[i].keep = data[i].keep;
		dst[i].strb = data[i].strb;
		dst[i].user = data[i].user;
		dst[i].last = data[i].last;
		dst[i].id = data[i].id;
		dst[i].dest = data[i].dest;
	}//cout << endl;

	dst[CLASSES-1].data = ((float)output[CLASSES-1])*DATA_CONVERT_MUL;//((int*)output)[i];
	//cout<<output[i]<<' '<<((float)output[i])<<' '<<((float)output[i])*DATA_CONVERT_MUL<<endl;
	dst[CLASSES-1].keep = data[CLASSES-1].keep;
	dst[CLASSES-1].strb = data[CLASSES-1].strb;
	dst[CLASSES-1].user = data[CLASSES-1].user;
	dst[CLASSES-1].last = 1;
	dst[CLASSES-1].id = data[CLASSES-1].id;
	dst[CLASSES-1].dest = data[CLASSES-1].dest;

	/*
	Output_fill:
	for(int i=CLASSES; i<BUFFER_SIZE; i++){
		dst[i].data = data[i].data;
		dst[i].keep = data[i].keep;
		dst[i].strb = data[i].strb;
		dst[i].user = data[i].user;
		dst[i].last = data[i].last;
		dst[i].id = data[i].id;
		dst[i].dest = data[i].dest;
	}*/

}
