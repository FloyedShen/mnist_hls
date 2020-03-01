/*
 * fullyconnected.cpp
 *
 *  Created on: 2020. 2. 27.
 *      Author: floyed
 */

#ifndef __FULLY_CONNECTED_H__
#define __FULLY_CONNECTED_H__

#include "parameters.h"

void Fully_Connected_Layer_1(hw_fixed* input_feature, hw_fixed* weights, hw_fixed* bias, hw_fixed* output_feature);
void Fully_Connected_Layer_2(hw_fixed* input_feature, hw_fixed* weights, hw_fixed* bias, hw_fixed* output_feature);


#endif
