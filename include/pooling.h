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

void Pooling_Layer_1(hw_fixed* src, hw_fixed* pool_kernel, hw_fixed* pool_bias, hw_fixed* dst);
void Pooling_Layer_2(hw_fixed* src, hw_fixed* pool_kernel, hw_fixed* pool_bias, hw_fixed* dst);
#endif
