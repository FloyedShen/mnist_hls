/*
 * LeNet_tb.cpp
 *
 *  Created on: 2020. 2. 27.
 *      Author: floyed
 */
#include "LeNet.h"
#include "iostream"
#include "fstream"
#include "cstring"
#include "ap_fixed.h"
//#include "opencv/cv.h"
#include "MNIST_DATA.h"
using namespace std;
//using namespace cv;
//#define float ap_fixed<32,2>

const string fname[] = {
		"/home/parallels/Documents/LeNet/Vivado_hls/filter/Wconv1.mdl",
		"/home/parallels/Documents/LeNet/Vivado_hls/filter/bconv1.mdl",
		"/home/parallels/Documents/LeNet/Vivado_hls/filter/Wconv3.mdl",
		"/home/parallels/Documents/LeNet/Vivado_hls/filter/bconv3.mdl",
		"/home/parallels/Documents/LeNet/Vivado_hls/filter/Wconv5.mdl",
		"/home/parallels/Documents/LeNet/Vivado_hls/filter/bconv5.mdl",
		"/home/parallels/Documents/LeNet/Vivado_hls/filter/Wpool1.mdl",
		"/home/parallels/Documents/LeNet/Vivado_hls/filter/bpool1.mdl",
		"/home/parallels/Documents/LeNet/Vivado_hls/filter/Wpool2.mdl",
		"/home/parallels/Documents/LeNet/Vivado_hls/filter/bpool2.mdl",
		"/home/parallels/Documents/LeNet/Vivado_hls/filter/Wfc1.mdl",
		"/home/parallels/Documents/LeNet/Vivado_hls/filter/bfc1.mdl",
		"/home/parallels/Documents/LeNet/Vivado_hls/filter/Wfc2.mdl",
		"/home/parallels/Documents/LeNet/Vivado_hls/filter/bfc2.mdl"
};

const int size[]={
		CONV_1_TYPE*CONV_1_SIZE,
		CONV_1_TYPE,
		CONV_2_TYPE*CONV_1_TYPE*CONV_2_SIZE/3,
		CONV_2_TYPE,
		CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE/50,
		CONV_3_TYPE,
		POOL_1_TYPE*4,
		POOL_1_TYPE,
		POOL_2_TYPE*4,
		POOL_2_TYPE,
		FILTER_NN_1_SIZE/21,
		BIAS_NN_1_SIZE,
		FILTER_NN_2_SIZE,
		BIAS_NN_2_SIZE
};

float MNIST_IMG[image_Move*MNIST_PAD_SIZE];
int MNIST_LABEL[image_Move];

void load_weight(string filename, ap_axis<32,1,1,1> *src, ap_axis<32,1,1,1>*dst,
		int length, int id){

	ifstream file(filename.c_str(), ios::in);
	if(file.is_open()){
		//printf("file opened\r\n");

		for(int i=0; i<length; i++){
			float tmp;
			file >> tmp;
			//float *ptr = &tmp;
			src[i].data = int(tmp*1000000);
			src[i].keep = 1;
			src[i].strb = 1;
			src[i].user = 1;
			src[i].last = 0;
			src[i].id = 0;
			src[i].dest = 1;
			//if(i == length-1)
			//	src[i].last = 1;
		}
	}
	else{
		printf("Open file failed\r\n");
	}
	LeNet(src, dst, id);
}

void load_weight_spc(string filename, ap_axis<32,1,1,1> *src, ap_axis<32,1,1,1> *dst,
		int length, int times, int id_begin){
	float data[length*times];

	ifstream file(filename.c_str(), ios::in);
	if(file.is_open()){
		for(int i=0; i<length*times; i++){
			float tmp;
			file >> tmp;
			data[i] = tmp;
		}
	}
	else{
		printf("Open file failed\r\n");
	}

	for(int t=0; t<times; t++){
		for(int i=0; i<length; i++){
			src[i].data = (data[t*length+i]*1000000);//((int*)data)[t*length + i];
			//cout <<src[i].data <<endl;
			src[i].keep = 1;
			src[i].strb = 1;
			src[i].user = 1;
			src[i].last = 0;
			src[i].id = 0;
			src[i].dest = 1;
			//if(i == length - 1)
			//	src[i].last = 1;
		}
		LeNet(src, dst, id_begin+t);
	}
}
int main(int argc, char* argv[]){
	printf("hello world\r\n");
	ap_axis<32,1,1,1> src[BUFFER_SIZE], dst[CLASSES];
	float result[CLASSES];

	load_weight(fname[0], src, dst, size[0], 1);
	load_weight(fname[1], src, dst, size[1], 2);
	load_weight_spc(fname[2], src, dst, size[2], 3, 3);
	load_weight(fname[3], src, dst, size[3], 6);
	load_weight_spc(fname[4], src, dst, size[4], 50, 7);
	load_weight(fname[5], src, dst, size[5], 57);
	load_weight(fname[6], src, dst, size[6], 58);
	load_weight(fname[7], src, dst, size[7], 59);
	load_weight(fname[8], src, dst, size[8], 60);
	load_weight(fname[9], src, dst, size[9], 61);
	load_weight_spc(fname[10], src, dst, size[10], 21, 62);
	load_weight(fname[11], src, dst, size[11], 83);
	load_weight(fname[12], src, dst, size[12], 84);
	load_weight(fname[13], src, dst, size[13], 85);

	READ_MNIST_DATA("/home/parallels/Documents/LeNet/Vivado_hls/MNIST_DATA/t10k-images.idx3-ubyte",
			MNIST_IMG,-1.0f, 1.0f, image_Move);
	READ_MNIST_LABEL("/home/parallels/Documents/LeNet/Vivado_hls/MNIST_DATA/t10k-labels.idx1-ubyte",
			MNIST_LABEL,image_Move,false);

	int test_num = image_Move / image_Batch;

	//int *MNIST_IMG_INT = (int*)MNIST_IMG;
	for(int i=0; i<test_num; i++){
		//cout <<"IMAGE ID: "<<i <<endl;
		char tmp;
		for(int batch=0; batch<image_Batch*INPUT_WH*INPUT_WH; batch++){
			//cout << MNIST_IMG[i*MNIST_PAD_SIZE + batch] <<' ';
			src[batch].data = int(MNIST_IMG[i*MNIST_PAD_SIZE + batch]*1000000);//((int*)MNIST_IMG)[i*MNIST_PAD_SIZE + batch];
			src[i].keep = 1;
			src[i].strb = 1;
			src[i].user = 1;
			src[i].last = 0;
			src[i].id = 0;
			src[i].dest = 1;
			//cout << src[batch].data <<endl;
			//ap_int<32> *float_ptr = &src[batch].data;
			//float res = *(float*)float_ptr;
			//printf("%x %d %lf %lf\r\n", src[batch].data, src[batch].data, src[batch].data, *float_ptr);
			//cout <<MNIST_IMG[i*MNIST_PAD_SIZE + batch]<<' ' << res <<endl;
		}cout << endl;
		LeNet(src, dst, 0);
		for(int index=0; index<10; index++){
			int tmp = dst[index].data;
			result[index] = tmp*1.0 / 1000000;//*(float*)(&tmp);
			cout <<result[index]<<' ';
		}
		cout << endl;
		cout << MNIST_LABEL[i] << endl;
	}
}
