/***************************** Include Files *********************************/
#include "time.h"
#include "xtime_l.h"
#include "xaxidma.h"
#include "xparameters.h"
#include "xdebug.h"
#include "xlenet.h"

#if defined(XPAR_UARTNS550_0_BASEADDR)
#include "xuartns550_l.h"       /* to use uartns550 */
#endif

/******************** Constant Definitions **********************************/

/*
 * Device hardware build related constants.
 */

#define DMA_DEV_ID		XPAR_AXIDMA_0_DEVICE_ID

#ifdef XPAR_AXI_7SDDR_0_S_AXI_BASEADDR
#define DDR_BASE_ADDR		XPAR_AXI_7SDDR_0_S_AXI_BASEADDR
#elif XPAR_MIG7SERIES_0_BASEADDR
#define DDR_BASE_ADDR	XPAR_MIG7SERIES_0_BASEADDR
#elif XPAR_MIG_0_BASEADDR
#define DDR_BASE_ADDR	XPAR_MIG_0_BASEADDR
#elif XPAR_PSU_DDR_0_S_AXI_BASEADDR
#define DDR_BASE_ADDR	XPAR_PSU_DDR_0_S_AXI_BASEADDR
#endif

#ifndef DDR_BASE_ADDR
#warning CHECK FOR THE VALID DDR ADDRESS IN XPARAMETERS.H, \
		 DEFAULT SET TO 0x01000000
#define MEM_BASE_ADDR		0x01000000
#else
#define MEM_BASE_ADDR		(DDR_BASE_ADDR + 0x1000000)
#endif

#define TX_BUFFER_BASE		(MEM_BASE_ADDR + 0x00000000)
#define RX_BUFFER_BASE		(MEM_BASE_ADDR + 0x03000000)
#define RX_BUFFER_HIGH		(MEM_BASE_ADDR + 0x004FFFFF)

#define MAX_SEN_LEN		1024
#define MAX_REC_LEN 	10


#define NUMBER_OF_TRANSFERS	100

/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/

#if (!defined(DEBUG))
extern void xil_printf(const char *format, ...);
#endif

int XAxiDma_SimplePollExample(u16 DeviceId);
static int CheckData(void);

/************************** Variable Definitions *****************************/
/*
 * Device instance definitions
 */
XAxiDma AxiDma;
XLenet xlenet;
int8_t *TxBufferPtr;
int8_t *RxBufferPtr;

#define IMAGE_SIZE 1024
#define DATA_CONVERT_MUL (1<<(5))
float MNIST_DATA[] = {
		#include "test_data.h"
};

/*****************************************************************************/
/**
* The entry point for this example. It invokes the example function,
* and reports the execution status.
*
* @param	None.
*
* @return
*		- XST_SUCCESS if example finishes successfully
*		- XST_FAILURE if example fails.
*
* @note		None.
*
******************************************************************************/
int main()
{
	int Status;

	xil_printf("\r\n--- Entering main() --- \r\n");

	//init HLS IP
	int _status = XLenet_Initialize(&xlenet,XPAR_LENET_0_DEVICE_ID);
	if(_status != XST_SUCCESS)
	{
		xil_printf("XExample_initialize failed\n");
		return XST_FAILURE;
	}

	//start HLS IP
	//XFifo_EnableAutoRestart(&xlenet);
	XLenet_Start(&xlenet);

	XLenet_Set_id(&xlenet, 0);
	int origin = XLenet_Get_id(&xlenet);
	xil_printf("Origin INC value: %d\r\n", origin);
	/* Run the poll example for simple transfer */
	Status = XAxiDma_SimplePollExample(DMA_DEV_ID);

	if (Status != XST_SUCCESS) {
		xil_printf("XAxiDma_SimplePoll Example Failed\r\n");
		return XST_FAILURE;
	}

	xil_printf("Successfully ran XAxiDma_SimplePoll Example\r\n");

	xil_printf("--- Exiting main() --- \r\n");

	return XST_SUCCESS;

}

#if defined(XPAR_UARTNS550_0_BASEADDR)
/*****************************************************************************/
/*
*
* Uart16550 setup routine, need to set baudrate to 9600, and data bits to 8
*
* @param	None.
*
* @return	None
*
* @note		None.
*
******************************************************************************/
static void Uart550_Setup(void)
{

	/* Set the baudrate to be predictable
	 */
	XUartNs550_SetBaud(XPAR_UARTNS550_0_BASEADDR,
			XPAR_XUARTNS550_CLOCK_HZ, 9600);

	XUartNs550_SetLineControlReg(XPAR_UARTNS550_0_BASEADDR,
			XUN_LCR_8_DATA_BITS);

}
#endif

/*****************************************************************************/
/**
* The example to do the simple transfer through polling. The constant
* NUMBER_OF_TRANSFERS defines how many times a simple transfer is repeated.
*
* @param	DeviceId is the Device Id of the XAxiDma instance
*
* @return
*		- XST_SUCCESS if example finishes successfully
*		- XST_FAILURE if error occurs
*
* @note		None
*
*
******************************************************************************/
int XAxiDma_SimplePollExample(u16 DeviceId)
{
	XAxiDma_Config *CfgPtr;
	int Status;
	int Index;

	TxBufferPtr = (int8_t *)TX_BUFFER_BASE;
	RxBufferPtr = (int8_t *)RX_BUFFER_BASE;

	/* Initialize the XAxiDma device.
	 */
	CfgPtr = XAxiDma_LookupConfig(DeviceId);
	if (!CfgPtr) {
		xil_printf("No config found for %d\r\n", DeviceId);
		return XST_FAILURE;
	}

	Status = XAxiDma_CfgInitialize(&AxiDma, CfgPtr);
	if (Status != XST_SUCCESS) {
		xil_printf("Initialization failed %d\r\n", Status);
		return XST_FAILURE;
	}

	if(XAxiDma_HasSg(&AxiDma)){
		xil_printf("Device configured as SG mode \r\n");
		return XST_FAILURE;
	}

	/* Disable interrupts, we use polling mode
	 */
	XAxiDma_IntrDisable(&AxiDma, XAXIDMA_IRQ_ALL_MASK,
						XAXIDMA_DEVICE_TO_DMA);
	XAxiDma_IntrDisable(&AxiDma, XAXIDMA_IRQ_ALL_MASK,
						XAXIDMA_DMA_TO_DEVICE);

	//disable the cache
    Xil_DCacheDisable();


    for(Index = 0; Index < NUMBER_OF_TRANSFERS; Index ++){
		for(int i=0; i<IMAGE_SIZE; i++){
			TxBufferPtr[Index*IMAGE_SIZE + i] = (int8_t)(MNIST_DATA[Index*IMAGE_SIZE + i] * DATA_CONVERT_MUL);
		}
	}

    XTime start;
    XTime_GetTime(&start);
    xil_printf("test begin: %x\r\n", start);
    usleep(10000000);

    XTime tmp_time;
    XTime_GetTime(&tmp_time);
    XTime_GetTime(&tmp_time);
    xil_printf("test end: %x \r\n", tmp_time);
	for(int k=0; k<100; k++){
		for(Index = 0; Index < NUMBER_OF_TRANSFERS; Index ++) {

			while(XLenet_IsDone(&xlenet)){
				//xil_printf("FIFO is busy\r\n");
			}
			XLenet_Start(&xlenet);
			//write to the TxBuffer and RxBuffer default value


			for(int i = 0; i < MAX_REC_LEN; i++){
					RxBufferPtr[i] = 0;
			}

			Status = XAxiDma_SimpleTransfer(&AxiDma,(UINTPTR) RxBufferPtr,
					MAX_REC_LEN*sizeof(int8_t), XAXIDMA_DEVICE_TO_DMA);

			if (Status != XST_SUCCESS) {
				return XST_FAILURE;
			}

			Status = XAxiDma_SimpleTransfer(&AxiDma,(UINTPTR) TxBufferPtr + Index*IMAGE_SIZE,
					MAX_SEN_LEN*sizeof(int8_t), XAXIDMA_DMA_TO_DEVICE);

			if (Status != XST_SUCCESS) {
				return XST_FAILURE;
			}

			while ((XAxiDma_Busy(&AxiDma,XAXIDMA_DEVICE_TO_DMA)) ||
				(XAxiDma_Busy(&AxiDma,XAXIDMA_DMA_TO_DEVICE))) {
					//printf("RX: %d, TX:%d", (XAxiDma_Busy(&AxiDma,XAXIDMA_DEVICE_TO_DMA)), (XAxiDma_Busy(&AxiDma,XAXIDMA_DMA_TO_DEVICE)));
					/* Wait */
			}

			//Status = CheckData();
			//if (Status != XST_SUCCESS) {
			//	return XST_FAILURE;
			//}
		}
		XTime tmp;
		XTime_GetTime(&tmp);
		XTime output = ((tmp-start)*1000000)/(COUNTS_PER_SECOND);
		xil_printf("%TIME: %x  ", (output));
		xil_printf(" %x\r\n", tmp);
	}
	/* Test finishes successfully
	 */
	return XST_SUCCESS;
}

/*****************************************************************************/
/*
*
* This function checks data buffer after the DMA transfer is finished.
*
* @param	None
*
* @return
*		- XST_SUCCESS if validation is successful.
*		- XST_FAILURE otherwise.
*
* @note		None.
*
******************************************************************************/
static int CheckData(void)
{
	/*
	xil_printf("\nThe TxData is\n");
	for(int _index=0;_index < MAX_SEN_LEN;_index++)
	{
		xil_printf("%x ",TxBufferPtr[_index]);
	}
	*/
	//xil_printf("\nThe RxData is\n");
	for(int _index=0;_index < MAX_REC_LEN;_index++)
	{
		xil_printf("%d ",RxBufferPtr[_index]);
	}
	xil_printf("\r\n");

	return XST_SUCCESS;
}
