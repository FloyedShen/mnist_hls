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

void LeNet(ap_axis<HW_DATA_WIDTH,1,1,1>src[BUFFER_SIZE], ap_axis<HW_DATA_WIDTH,1,1,1>dst[CLASSES], int id){

	ap_int<HW_DATA_WIDTH> data[BUFFER_SIZE];
	for(int i=0; i<BUFFER_SIZE; i++){
//#pragma HLS pipeline
		data[i] = src[i].data;
	}

	//weither to init weight & bias
	static int init = 1;

	//conv layer weight & bias
	static hw_fixed Wconv1[CONV_1_TYPE*CONV_1_SIZE];
	static hw_fixed Bconv1[CONV_1_TYPE];
	static hw_fixed Wconv2[CONV_2_TYPE*CONV_1_TYPE*CONV_2_SIZE]; //spc
	static hw_fixed Bconv2[CONV_2_TYPE];
	static hw_fixed Wconv3[CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE]; //spc
	static hw_fixed Bconv3[CONV_3_TYPE];

	//pool layer weight & bias
	static hw_fixed Wpool1[POOL_1_TYPE*4];
	static hw_fixed Bpool1[POOL_1_TYPE];
	static hw_fixed Wpool2[POOL_2_TYPE*4];
	static hw_fixed Bpool2[POOL_2_TYPE];

	//fc layer weight & bias
	static hw_fixed Wfc1[FILTER_NN_1_SIZE];
	static hw_fixed Bfc1[BIAS_NN_1_SIZE];
	static hw_fixed Wfc2[FILTER_NN_2_SIZE];
	static hw_fixed Bfc2[BIAS_NN_2_SIZE];

	//load_model
	switch(id){
		case(1):LeNet_label54:{
			load_model(data, Wconv1, CONV_1_TYPE*CONV_1_SIZE);
			break;
		}
		case(2):LeNet_label81:{
			load_model(data, Bconv1, CONV_1_TYPE);
			break;
		}
		case(3):LeNet_label9:{
			load_model(data, Wconv2, CONV_2_TYPE*CONV_1_TYPE*CONV_2_SIZE/3);
			break;
		}
		case(4):LeNet_label58:{
			load_model(data, Wconv2+CONV_2_TYPE*CONV_1_TYPE*CONV_2_SIZE/3, CONV_2_TYPE*CONV_1_TYPE*CONV_2_SIZE/3);
			break;
		}
		case(5):LeNet_label39:{
			load_model(data, Wconv2+CONV_2_TYPE*CONV_1_TYPE*CONV_2_SIZE/3*2, CONV_2_TYPE*CONV_1_TYPE*CONV_2_SIZE/3);
			break;
		}
		case(6):LeNet_label21:{
			load_model(data, Bconv2, CONV_2_TYPE);
			break;
		}
		case(7):LeNet_label4:{
			load_model(data, Wconv3, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(8):LeNet_label48:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*1, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(9):LeNet_label76:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*2, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(10):LeNet_label63:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*3, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(11):LeNet_label19:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*4, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(12):LeNet_label44:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*5, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(13):LeNet_label25:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*6, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(14):LeNet_label35:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*7, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(15):LeNet_label40:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*8, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(16):LeNet_label72:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*9, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(17):LeNet_label66:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*10, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(18):LeNet_label84:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*11, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(19):LeNet_label57:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*12, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(20):LeNet_label0:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*13, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(21):LeNet_label80:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*14, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(22):LeNet_label61:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*15, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(23):LeNet_label83:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*16, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(24):LeNet_label5:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*17, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(25):LeNet_label49:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*18, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(26):LeNet_label38:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*19, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(27):LeNet_label24:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*20, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(28):LeNet_label62:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*21, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(29):LeNet_label69:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*22, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(30):LeNet_label52:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*23, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(31):LeNet_label34:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*24, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(32):LeNet_label46:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*25, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(33):LeNet_label43:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*26, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(34):LeNet_label73:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*27, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(35):LeNet_label70:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*28, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(36):LeNet_label16:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*29, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(37):LeNet_label82:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*30, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(38):LeNet_label79:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*31, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(39):LeNet_label6:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*32, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(40):LeNet_label10:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*33, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(41):LeNet_label45:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*34, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(42):LeNet_label14:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*35, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(43):LeNet_label68:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*36, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(44):LeNet_label7:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*37, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(45):LeNet_label53:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*38, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(46):LeNet_label22:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*39, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(47):LeNet_label15:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*40, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(48):LeNet_label28:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*41, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(49):LeNet_label74:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*42, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(50):LeNet_label50:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*43, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(51):LeNet_label12:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*44, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(52):LeNet_label77:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*45, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(53):LeNet_label56:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*46, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(54):LeNet_label11:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*47, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(55):LeNet_label30:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*48, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(56):LeNet_label29:{
			load_model(data, Wconv3+(CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50*49, (CONV_3_TYPE*CONV_2_TYPE*CONV_3_SIZE)/50);
			break;
		}
		case(57):LeNet_label75:{
			load_model(data, Bconv3, CONV_3_TYPE);
			break;
		}
		case(58):LeNet_label1:{
			load_model(data, Wpool1, POOL_1_TYPE*4);
			break;
		}
		case(59):LeNet_label59:{
			load_model(data, Bpool1, POOL_1_TYPE);
			break;
		}
		case(60):LeNet_label60:{
			load_model(data, Wpool2, POOL_2_TYPE*4);
			break;
		}
		case(61):LeNet_label71:{
			load_model(data, Bpool2, POOL_2_TYPE);
			break;
		}
		case(62):LeNet_label2:{
			load_model(data, Wfc1, FILTER_NN_1_SIZE/21);
			break;
		}
		case(63):LeNet_label17:{
			load_model(data, Wfc1+(FILTER_NN_1_SIZE/21), FILTER_NN_1_SIZE/21);
			break;
		}
		case(64):LeNet_label67:{
			load_model(data, Wfc1+(FILTER_NN_1_SIZE/21*2), FILTER_NN_1_SIZE/21);
			break;
		}
		case(65):LeNet_label13:{
			load_model(data, Wfc1+(FILTER_NN_1_SIZE/21*3), FILTER_NN_1_SIZE/21);
			break;
		}
		case(66):LeNet_label23:{
			load_model(data, Wfc1+(FILTER_NN_1_SIZE/21*4), FILTER_NN_1_SIZE/21);
			break;
		}
		case(67):LeNet_label37:{
			load_model(data, Wfc1+(FILTER_NN_1_SIZE/21*5), FILTER_NN_1_SIZE/21);
			break;
		}
		case(68):LeNet_label33:{
			load_model(data, Wfc1+(FILTER_NN_1_SIZE/21*6), FILTER_NN_1_SIZE/21);
			break;
		}
		case(69):LeNet_label47:{
			load_model(data, Wfc1+(FILTER_NN_1_SIZE/21*7), FILTER_NN_1_SIZE/21);
			break;
		}
		case(70):LeNet_label51:{
			load_model(data, Wfc1+(FILTER_NN_1_SIZE/21*8), FILTER_NN_1_SIZE/21);
			break;
		}
		case(71):LeNet_label78:{
			load_model(data, Wfc1+(FILTER_NN_1_SIZE/21*9), FILTER_NN_1_SIZE/21);
			break;
		}
		case(72):LeNet_label31:{
			load_model(data, Wfc1+(FILTER_NN_1_SIZE/21*10), FILTER_NN_1_SIZE/21);
			break;
		}
		case(73):LeNet_label26:{
			load_model(data, Wfc1+(FILTER_NN_1_SIZE/21*11), FILTER_NN_1_SIZE/21);
			break;
		}
		case(74):LeNet_label18:{
			load_model(data, Wfc1+(FILTER_NN_1_SIZE/21*12), FILTER_NN_1_SIZE/21);
			break;
		}
		case(75):LeNet_label36:{
			load_model(data, Wfc1+(FILTER_NN_1_SIZE/21*13), FILTER_NN_1_SIZE/21);
			break;
		}
		case(76):LeNet_label32:{
			load_model(data, Wfc1+(FILTER_NN_1_SIZE/21*14), FILTER_NN_1_SIZE/21);
			break;
		}
		case(77):LeNet_label55:{
			load_model(data, Wfc1+(FILTER_NN_1_SIZE/21*15), FILTER_NN_1_SIZE/21);
			break;
		}
		case(78):LeNet_label42:{
			load_model(data, Wfc1+(FILTER_NN_1_SIZE/21*16), FILTER_NN_1_SIZE/21);
			break;
		}
		case(79):LeNet_label65:{
			load_model(data, Wfc1+(FILTER_NN_1_SIZE/21*17), FILTER_NN_1_SIZE/21);
			break;
		}
		case(80):LeNet_label64:{
			load_model(data, Wfc1+(FILTER_NN_1_SIZE/21*18), FILTER_NN_1_SIZE/21);
			break;
		}
		case(81):LeNet_label8:{
			load_model(data, Wfc1+(FILTER_NN_1_SIZE/21*19), FILTER_NN_1_SIZE/21);
			break;
		}
		case(82):LeNet_label27:{
			load_model(data, Wfc1+(FILTER_NN_1_SIZE/21*20), FILTER_NN_1_SIZE/21);
			break;
		}
		case(83):LeNet_label3:{
			load_model(data, Bfc1, BIAS_NN_1_SIZE);
			break;
		}
		case(84):LeNet_label20:{
			load_model(data, Wfc2, FILTER_NN_2_SIZE);
			break;
		}
		case(85):LeNet_label41:{
			load_model(data, Bfc2, BIAS_NN_2_SIZE);
			break;
		}
		default: break;
	}

	//cout << id << endl;
	//debug(Wconv1, CONV_1_TYPE*CONV_1_SIZE, "WConv1");
	//debug(Bconv1, CONV_1_TYPE, "Bconv1");

	if(id != 0)
		return;

	//create layer
	hw_fixed input[image_Batch*INPUT_WH*INPUT_WH];
	hw_fixed conv1[image_Batch*CONV_1_TYPE*CONV_1_OUTPUT_SIZE];
	hw_fixed pool1[image_Batch*CONV_1_TYPE*POOL_1_OUTPUT_SIZE];
	hw_fixed conv2[image_Batch*CONV_2_TYPE*CONV_2_OUTPUT_SIZE];
	hw_fixed pool2[image_Batch*CONV_2_TYPE*CONV_2_OUTPUT_SIZE];
	hw_fixed conv3[image_Batch*CONV_3_TYPE*CONV_3_OUTPUT_SIZE];
	hw_fixed fc1[image_Batch*OUTPUT_NN_1_SIZE];
	hw_fixed output[image_Batch*OUTPUT_NN_2_SIZE];

	//load_image
	load_img(data, input);
	//cout<<"loaded image"<<endl;
	//calc
	Convolution_Layer_1(input, Wconv1, Bconv1, conv1, init);
	//cout<<"conv1"<<endl;
	Pooling_Layer_1(conv1, Wpool1, Bpool1, pool1);
	//cout<<"pool1"<<endl;
	Convolution_Layer_2(pool1, Wconv2, Bconv2, conv2, init);
	//cout<<"conv2"<<endl;
	Pooling_Layer_2(conv2, Wpool2, Bpool2, pool2);
	//cout<<"pool2"<<endl;
	Convolution_Layer_3(pool2, Wconv3, Bconv3, conv3, init);
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

	if(init)	init=0;

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
