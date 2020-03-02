/*
 * convolution.cpp
 *
 *  Created on: 2020. 2. 27.
 *      Author: floyed
 */
#include "convolution.h"
#include "hls_math.h"

void Convolution_Layer_1(const hw_fixed IBRAM[image_Batch][CONV_1_INPUT_WH][CONV_1_INPUT_WH],
		const hw_fixed WBRAM[CONV_1_TYPE][CONV_1_WH][CONV_1_WH],
		const hw_fixed biasBRAM[CONV_1_TYPE],
		hw_fixed OBRAM[image_Batch][CONV_1_TYPE][CONV_1_OUTPUT_WH][CONV_1_OUTPUT_WH]
		){

	BATCH :
	for(int batch=0; batch<image_Batch; batch++) {
		ROW_K:
		for(int row_k=0;row_k<CONV_1_WH;row_k++){
			COL_K:
			for(int col_k=0;col_k<CONV_1_WH;col_k++){
				ROW :
				for (int row = 0; row < CONV_1_OUTPUT_WH; row++) {
					COL:
					for (int col = 0; col < CONV_1_OUTPUT_WH; col++) {
						D_OUT:
						for(int co=0;co<CONV_1_TYPE;co++){
							if(!row_k&&!col_k)
								OBRAM[batch][co][row][col]
								  = IBRAM[batch][row+row_k][col+col_k]*WBRAM[co][row_k][col_k];
							else
								OBRAM[batch][co][row][col]
								  += IBRAM[batch][row+row_k][col+col_k]*WBRAM[co][row_k][col_k];
						}
					}
				}
			}
		}
	}
	biasBatch:
	for(int batch=0; batch<image_Batch; batch++){
		biasRow:
		for(int row=0; row<CONV_1_OUTPUT_WH; row++){
			biasCol:
			for(int col=0; col<CONV_1_OUTPUT_WH; col++){
				biasDepthIn:
				for(int depth=0; depth<CONV_1_TYPE; depth++){
					OBRAM[batch][depth][row][col] = _tanh(OBRAM[batch][depth][row][col] + biasBRAM[depth]);
				}
			}
		}
	}
}

void Convolution_Layer_2(const hw_fixed IBRAM[image_Batch][CONV_1_TYPE][CONV_2_INPUT_WH][CONV_2_INPUT_WH],
		const hw_fixed  WBRAM[CONV_2_TYPE][CONV_1_TYPE][CONV_2_WH][CONV_2_WH],
		const hw_fixed biasBRAM[CONV_2_TYPE],
		hw_fixed OBRAM[image_Batch][CONV_2_TYPE][CONV_2_OUTPUT_WH][CONV_2_OUTPUT_WH]
		){

	BATCH :
	for (int batch = 0; batch < image_Batch; batch++) {
		ROW_K:
		for(int row_k = 0;row_k<CONV_2_WH;row_k++){
			COL_K:
			for(int col_k=0;col_k<CONV_2_WH;col_k++){
				ROW :
				for (int row = 0; row < CONV_2_OUTPUT_WH; row++) {
					COL	 :
					for (int col = 0; col < CONV_2_OUTPUT_WH; col++) {
						DEPTH_OUT:
						for(int depth_out = 0; depth_out < CONV_2_TYPE; depth_out++){
							DEPTH_IN:
							for (int depth_in = 0; depth_in < CONV_1_TYPE; depth_in++) {
								if(!row_k&&!col_k&&!depth_in){
									if(tbl[depth_in*16+depth_out])
									OBRAM[batch][depth_out][row][col]
											= IBRAM[batch][depth_in][row+row_k][col+col_k]
													*WBRAM[depth_out][depth_in][row_k][col_k];
									else OBRAM[batch][depth_out][row][col] = 0;
								}
								else if(tbl[depth_in*16+depth_out]){
									OBRAM[batch][depth_out][row][col]
											+= IBRAM[batch][depth_in][row+row_k][col+col_k]
												      *WBRAM[depth_out][depth_in][row_k][col_k];
								}
							}
						}
					}
				}
			}
		}
	}
	biasBatch:
	for(int batch=0; batch<image_Batch; batch++){
		biasROW:
		for(int row=0; row<CONV_2_OUTPUT_WH; row++){
			biasCOL:
			for(int col=0; col<CONV_2_OUTPUT_WH; col++){
				biasDEPTH:
				for(int depth=0; depth<CONV_2_TYPE; depth++){
					OBRAM[batch][depth][row][col] = _tanh(OBRAM[batch][depth][row][col] + biasBRAM[depth]);
				}
			}
		}
	}

}


void Convolution_Layer_3(const hw_fixed IBRAM[image_Batch][CONV_2_TYPE][CONV_3_INPUT_WH][CONV_3_INPUT_WH],
		const hw_fixed WBRAM[CONV_3_TYPE][CONV_2_TYPE][CONV_3_WH][CONV_3_WH],
		const hw_fixed biasBRAM[CONV_3_TYPE],
		hw_fixed OBRAM[image_Batch][CONV_3_TYPE]
		){

	BATCH:
	for (int batch = 0; batch<image_Batch; batch++) {
		ROW_K:
		for(int row_k=0;row_k<CONV_3_WH;row_k++){
			COL_K:
			for(int col_k=0;col_k<CONV_3_WH;col_k++){
				D_OUT:
				for(int co=0;co<CONV_3_TYPE;co++){
					D_IN:
					for(int ci=0;ci<CONV_2_TYPE;ci++){
						if(!row_k&&!col_k){
							OBRAM[batch][co]
							  = IBRAM[batch][ci][row_k][col_k]*WBRAM[co][ci][row_k][col_k];
						}
						else{
							OBRAM[batch][co]
							  += IBRAM[batch][ci][row_k][col_k]*WBRAM[co][ci][row_k][col_k];
						}
					}
				}
			}
		}
	}
	biasBatch:
	for(int i=0;i<image_Batch;i++){
		biasDepth:
		for(int j=0;j<CONV_3_TYPE;j++){
			OBRAM[i][j] = _tanh(OBRAM[i][j]+biasBRAM[j]);
		}
	}
}

