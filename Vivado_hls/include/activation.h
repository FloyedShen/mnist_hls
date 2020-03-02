/*
 * activation.h
 *
 *  Created on: 2020. 2. 27.
 *      Author: floyed
 */
#ifndef SRC_LENET5_HW_LAYERS_ACTIVATION_H_
#define SRC_LENET5_HW_LAYERS_ACTIVATION_H_

#include "parameters.h"

const hw_fixed tanh_index[] = {
	#include "tanh_index.h"
};

const hw_fixed tanh_value[] = {
	#include"tanh_value.h"
};

hw_fixed _tanh(const hw_fixed &x);
hw_fixed relu(const hw_fixed &x);




#endif /* SRC_LENET5_HW_LAYERS_ACTIVATION_H_ */
