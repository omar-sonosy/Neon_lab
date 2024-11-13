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
	int i;
	for(i=0;i<10;i++)
		print("Hello World\n\r");
	XTime_GetTime(&end);
	printf("%llu\n\r",end-start);
	
    cleanup_platform();
    return 0;
}
