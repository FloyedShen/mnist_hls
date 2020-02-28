/*
 *  pooling.h
 *
 *  Created on: 2020. 2. 27.
 *      Author: floyed
 */

#ifndef __POOLING_H__
#define __POOLING_H__

#include "activation.h"
#include "parameters.h"

void Pooling_Layer_1(float* src, float* pool_kernel, float* pool_bias, float* dst);
void Pooling_Layer_2(float* src, float* pool_kernel, float* pool_bias, float* dst);
#endif
