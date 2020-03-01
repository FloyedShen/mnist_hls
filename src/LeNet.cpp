/*
 * LeNet.cpp
 *
 *  Created on: 2020. 2. 27.
 *      Author: floyed
 */
#include "LeNet.h"
#include "iostream"
#include "cstring"
#include "ap_fixed.h"
using namespace std;
/*
void load_model(ap_int<HW_DATA_WIDTH> *src, hw_fixed *dst, int length){
	for(int i=0; i<length; i++){
//#pragma HLS pipeline
		dst[i] = ((float)src[i])/DATA_CONVERT_MUL;//((float*)src)[i];
	}
	return;
}

void load_img(ap_int<HW_DATA_WIDTH> *src, hw_fixed *img){
	for(int i=0; i<image_Batch*INPUT_WH*INPUT_WH; i++){
//#pragma HLS pipeline
		img[i] = ((float)src[i])/DATA_CONVERT_MUL;//((float*)src)[i];
		//if(img[i] != -1)
		//cout <<src[i].data<<' '<< img[i] << endl;
	}//cout<<endl;
	return;
}
#ifndef __SYNTHESIS__
void debug(hw_fixed *data, int length, string name){
	//cout << name << endl;
	for(int i=0; i<length; i++)
		cout << data[i] << ' ';
	cout << endl;
}
#endif
*/
void LeNet(ap_axis<HW_DATA_WIDTH,1,1,1>src[BUFFER_SIZE], ap_axis<HW_DATA_WIDTH,1,1,1>dst[CLASSES], int id){

	//weither to init weight & bias
	//static int init = 1;

	//conv layer weight & bias
	const hw_fixed Wconv1[CONV_1_TYPE][CONV_1_WH][CONV_1_WH] = {
#include "Wconv1.h"
	};
	const hw_fixed Bconv1[CONV_1_TYPE] = {
#include "bconv1.h"
	};
	const hw_fixed Wconv2[CONV_2_TYPE][CONV_1_TYPE][CONV_2_WH][CONV_2_WH] = {
#include "Wconv3.h"
	};
	const hw_fixed Bconv2[CONV_2_TYPE] = {
#include "bconv3.h"
	};
	const hw_fixed Wconv3[CONV_3_TYPE][CONV_2_TYPE][CONV_3_WH][CONV_3_WH] = {
#include "Wconv5.h"
	};
	const hw_fixed Bconv3[CONV_3_TYPE] = {
#include "bconv5.h"
	};

	//pool layer weight & bias
	const hw_fixed Wpool1[POOL_1_TYPE*4] = {
#include "Wpool1.h"
	};
	const hw_fixed Bpool1[POOL_1_TYPE] = {
#include "bpool1.h"
	};
	const hw_fixed Wpool2[POOL_2_TYPE*4] = {
#include "Wpool2.h"
	};
	const hw_fixed Bpool2[POOL_2_TYPE] = {
#include "bpool2.h"
	};

	//fc layer weight & bias
	const hw_fixed Wfc1[FILTER_NN_1_SIZE] = {
#include "Wfc1.h"
	};
	const hw_fixed Bfc1[BIAS_NN_1_SIZE] = {
#include "bfc1.h"
	};
	const hw_fixed Wfc2[FILTER_NN_2_SIZE] = {
#include "Wfc2.h"
	};
	const hw_fixed Bfc2[BIAS_NN_2_SIZE] = {
#include "bfc2.h"
	};

	if(id != 0)
		return;
	/*
	for(int i=0;i<CONV_1_TYPE;i++){
		for(int j=0;j<5;j++){
			for(int k=0;k<5;k++){
//#pragma HLS pipeline
//#pragma HLS UNROLL
				cout << Wconv1[i][j][k] << ' ';
			}
		}
	}cout << endl;
	*/
	//create layer
	hw_fixed input[image_Batch][INPUT_WH][INPUT_WH];
	hw_fixed conv1[image_Batch][CONV_1_TYPE][CONV_1_OUTPUT_WH][CONV_1_OUTPUT_WH];
	hw_fixed pool1[image_Batch][CONV_1_TYPE][CONV_2_INPUT_WH][CONV_2_INPUT_WH];
	hw_fixed conv2[image_Batch][CONV_2_TYPE][CONV_2_OUTPUT_WH][CONV_2_OUTPUT_WH];
	hw_fixed pool2[image_Batch][CONV_2_TYPE][CONV_3_INPUT_WH][CONV_3_INPUT_WH];
	hw_fixed conv3[image_Batch][CONV_3_TYPE];
	hw_fixed fc1[image_Batch][OUTPUT_NN_1_SIZE];
	hw_fixed output[image_Batch*OUTPUT_NN_2_SIZE];

	for(int batch=0; batch<image_Batch; batch++){
		for(int i=0; i<INPUT_WH; i++){
			for(int j=0; j<INPUT_WH; j++){
				input[batch][i][j] = ((float)src[i*INPUT_WH+j].data)/DATA_CONVERT_MUL;
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
/*

	debug(Wconv1, CONV_1_TYPE*CONV_1_SIZE, "WConv1");
	debug(Bconv1, CONV_1_TYPE, "Bconv1");
	debug(Wconv2, CONV_2_TYPE*CONV_1_TYPE*CONV_2_SIZE, "WConv2"); //Error
	debug(Bconv2, CONV_2_TYPE, "Bconv2");
	debug(Wconv3, CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE, "WConv3");
	debug(Bconv3, CONV_3_TYPE, "Bconv3");
	debug(Wpool1, POOL_1_TYPE*4, "Wpool1");
	debug(Bpool1, CONV_1_TYPE, "Bpool1");
	debug(Wpool2, POOL_2_TYPE*4, "Wpool2");
	debug(Bpool2, CONV_2_TYPE, "Bpool2");
	debug(Wfc1, FILTER_NN_1_SIZE, "Wfc1");
	debug(Bfc1, BIAS_NN_1_SIZE, "Bfc1");
	debug(Wfc2, FILTER_NN_2_SIZE, "Wfc2");
	debug(Bfc2, BIAS_NN_2_SIZE, "Bfc2");

	debug(output, image_Batch*OUTPUT_NN_2_SIZE, "output");
*/

	//debug(Wconv1, CONV_1_TYPE*CONV_1_SIZE, "WConv1");
	//debug(conv1, image_Batch*CONV_1_TYPE*CONV_1_OUTPUT_SIZE, "Conv1");
	//debug(pool1, image_Batch*CONV_2_TYPE*POOL_2_OUTPUT_SIZE, "Pool2");
	//debug(output, image_Batch*OUTPUT_NN_2_SIZE, "output");

	for(int i=0; i<CLASSES; i++){
//#pragma HLS pipeline
		dst[i].data = ((float)output[i])*DATA_CONVERT_MUL;//((int*)output)[i];
		//cout<<output[i]<<' '<<((float)output[i])<<' '<<((float)output[i])*DATA_CONVERT_MUL<<endl;
		dst[i].keep = 1;
		dst[i].strb = 1;
		dst[i].user = 1;
		dst[i].last = 0;
		dst[i].id = 0;
		dst[i].dest = 1;
	}//cout << endl;
}
