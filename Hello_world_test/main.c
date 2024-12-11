#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xtime_l.h"
#include "xparameters.h"

int main()
{
	XTime start;
	XTime end;
	//double total_time;
    init_platform();
	XTime_GetTime(&start);
	print("Hello World\n\r");
	XTime_GetTime(&end);
	float time_ms= ((end-start)*2.0)*1000000/XPAR_CPU_CORTEXA9_0_CPU_CLK_FREQ_HZ;
	printf("%f micro_s\n\r",time_ms);
	
    cleanup_platform();
    return 0;
}
