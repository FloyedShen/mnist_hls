/*
 * activation.cpp
 *
 *  Created on: 2020. 2. 27.
 *      Author: floyed
 */
#include "activation.h"

float _tanh(float x){
#pragma HLS INLINE
	float exp2x = expf(2*x)+1;
	return (exp2x-2)/(exp2x);
}

float relu(float x){
#pragma HLS inline
	return x>0 ? x : 0;
}

