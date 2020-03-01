/*
 * activation.cpp
 *
 *  Created on: 2020. 2. 27.
 *      Author: floyed
 */
#include "activation.h"
//#include "iostream"
//using namespace std;
hw_fixed _tanh(hw_fixed x){
#pragma HLS INLINE
	float exp2x = expf(2*(float)x)+1;
	//cout <<x<<' '<<exp2x<<' '<<(hw_fixed)((exp2x-2)/(exp2x))<<endl;
	return (hw_fixed)((exp2x-2)/(exp2x));
}

hw_fixed relu(hw_fixed x){
#pragma HLS inline
	if(x>0) return x;
	else return 0;
}

