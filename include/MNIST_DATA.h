#ifndef SRC_MNIST_DATA_H_
#define SRC_MNIST_DATA_H_
#include <iostream>
#include <fstream>
#include "parameters.h"

#define TRUE 1
#define FALSE 0
using namespace std;
int ReverseInt(int i);

void READ_MNIST_DATA(string filename, float* arr, float scale_min,
		float scale_max, int image_num=image_Move);

void READ_MNIST_LABEL(string filename, int* label, int image_num=10000,
		int one_hot = TRUE);

void preprocessTestImage(float* input_layer,
		unsigned char* test_img, float scale_min, float scale_max);
#endif
