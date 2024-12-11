#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xtime_l.h"
#include "xparameters.h"
#include "stdint.h"

int sum_c(int16_t* arr)
{
	int sum=0;
	for(int i = 0; i < 2048; i++)
	{
		sum+=(int)arr[i];
	}
	return sum;
}
int main()
{
	XTime start;
	XTime end;
	
	//double total_time;
    init_platform();
	int16_t arr[2048];
	int sum;
	for(int i=0;i<2048;i++)
		arr[i]=(int16_t)1;
	
	XTime_GetTime(&start);
	sum= sum_c(arr);
	XTime_GetTime(&end);
	printf("Sum of array= %d\n\r",sum);
	float time_ms= ((end-start)*2.0)*1000000/XPAR_CPU_CORTEXA9_0_CPU_CLK_FREQ_HZ;
	printf("Time of summing array in C: %f micro_s\n\r",time_ms);
	
    cleanup_platform();
    return 0;
}
